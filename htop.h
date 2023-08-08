#pragma once

#include <thread>
#include <condition_variable>

#include "data.h"
#include "data_miner.h"
#include "measurement.h"
#include "viewer.h"
#include "worker.h"
#include "worker_core_cpu.h"
#include "worker_common_cpu.h"

class Htop {
private:
    int count_data;
    int count_threads;
    int count_wait_threads;
    int index_current_samples;
    int index_main_graph;
    std::mutex synchronize;
    std::mutex print_console_buffer;
    std::condition_variable cv;
    Viewer viewer;
    DataMiner data_miner;   
    Data<Measurement> data;
    Data<Data<float>> samples;
    WorkerCoreCpu worker_core_cpu;
    WorkerCommonCpu worker_common_cpu;
    bool testWorkStatus();
    void makeSynchronizeThread();
    void prepareForNextItearation();
    void workByThread(Worker& worker,int index);
public:
    Htop();
    void startProgramme();
};