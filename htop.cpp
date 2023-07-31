#include <string>
#include <chrono>
#include <iostream>
#include <vector>
#include <unistd.h>

#include "htop.h"

constexpr int TIME_DELAY = 1500;           /* orignal htop has the same delay */

void Htop::makeSynchronizeThread() {
    std::unique_lock<std::mutex> lk(synchronize);
    count_wait_threads++;
    if (count_wait_threads == count_threads) {
        viewer.updateConsole();
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_DELAY));
        data_miner.updateData(data);
        count_wait_threads = 0;
        cv.notify_all();
    } else {
        cv.wait(lk);                       /* TODO: add predicate */
    }
}

void Htop::workByThread(Worker& worker, int index) {
    std::string output = worker.getStartOutput(index);
    while (testWorkStatus()) {
        worker.calculateUsage(data[index]);
        print_console_buffer.lock();
        viewer.printConsoleBuffer(output, data[index].utilization, index);        
        print_console_buffer.unlock();
        makeSynchronizeThread();
  }
}

/* TODO: make it possible to stop by pressing the button */
bool Htop::testWorkStatus() {
    return true;
};

Htop::Htop() {
    count_core = sysconf(_SC_NPROCESSORS_CONF);
    count_data = count_core + 1;                   /* cores + common */
    count_threads = count_data;
    count_wait_threads = 0;
    data = Data<Measurement>(count_data);
    data_miner.updateData(data);
}

void Htop::startProgramme() {
    std::vector<std::thread> threads = std::vector<std::thread>(count_data);
    threads[0] = std::thread(&Htop::workByThread, this, std::ref(worker_common_cpu), 0);
    for (int index = 1; index < count_threads; index++) {
         threads[index] = std::thread(&Htop::workByThread, this, std::ref(worker_core_cpu), index);
    }
    for (int index = 0; index < count_threads; index++) {
        threads[index].join();
    }
}
