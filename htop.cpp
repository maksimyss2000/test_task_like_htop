#include <string>
#include <chrono>
#include <iostream>
#include <vector>
#include <unistd.h>

#include "htop.h"

constexpr int TIME_DELAY = 1500;           /* orignal htop has the same delay */
constexpr int COUNT_SAMPLES = 25;


void Htop::prepareForNextItearation(){
    data_miner.updateData(data);
    index_current_sample = (index_current_sample + 1) % COUNT_SAMPLES;
    count_wait_threads = 0;
}

void Htop::makeSynchronizeThread() {
    std::unique_lock<std::mutex> lk(synchronize);
    count_wait_threads++;
    if (count_wait_threads == count_threads) {
        viewer.updateConsole();
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_DELAY));
        prepareForNextItearation();
        cv.notify_all();
    } else {
        cv.wait(lk);                       /* TODO: add predicate */
    }
}

void Htop::workByThread(Worker& worker, int index_thread) {
    std::string output = worker.getStartOutput(index_thread);
    while (testWorkStatus()) {
        worker.calculateUsage(data[index_thread], samples[index_thread][index_current_sample]);
        print_console_buffer.lock();
        viewer.printConsoleBuffer(output, samples[index_thread][index_current_sample], index_thread);      
        if (index_main_graph == index_thread) {
            viewer.printGraph(output, samples[index_thread], index_current_sample);
        }
        print_console_buffer.unlock();  
        makeSynchronizeThread();
  }
}

/* TODO: make it possible to stop by pressing the button */
bool Htop::testWorkStatus() {
    return true;
};

Htop::Htop() {
    index_main_graph = 0;
    index_current_sample = 0;
    count_wait_threads = 0;

    int count_core = sysconf(_SC_NPROCESSORS_CONF);
    count_data = count_core + 1;                   /* cores + common */
    count_threads = count_data;

    data = Data<Measurement>(count_data);
    samples = Data<Data<float>>(count_data);
    for (auto& elem: samples){
        elem = Data<float>(COUNT_SAMPLES);
        for (auto& value: elem) {
            value = 0;
        }
    }

    data_miner.updateData(data);
    viewer.setUsedParameters(count_threads, COUNT_SAMPLES);
}

void Htop::startProgramme() {
    std::vector<std::thread> threads = std::vector<std::thread>(count_data);
    threads[0] = std::thread(&Htop::workByThread, this, std::ref(worker_common_cpu), 0);
    for (int index_thread = 1; index_thread < count_threads; index_thread++) {
         threads[index_thread] = std::thread(&Htop::workByThread, this, std::ref(worker_core_cpu), index_thread);
    }
    for (int index_thread = 0; index_thread < count_threads; index_thread++) {
        threads[index_thread].join();
    }
}