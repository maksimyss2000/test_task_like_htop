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
public:
    Htop();
    void startProgramme();
private:
    int count_core;
    int count_data;
    int count_threads;
    int count_wait_threads;
    std::mutex synchronize;
    std::mutex print_console_buffer;
    std::condition_variable cv;
    Viewer viewer;
    DataMiner data_miner;   
    Data<Measurement> data;
    WorkerCoreCpu worker_core_cpu;
    WorkerCommonCpu worker_common_cpu;
    void makeSynchronizeThread();
    void workByThread(Worker& worker,int index);
    bool testWorkStatus();
};