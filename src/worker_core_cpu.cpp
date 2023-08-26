#include <numeric>
#include <iostream>

#include "worker_core_cpu.h"

void WorkerCoreCpu::calculateUsage(Measurement& measurement, float& utilization) {
    measurement.total_time_prev = measurement.total_time_curr;
    measurement.total_time_curr = std::accumulate(measurement.curr.begin(), measurement.curr.end(), 0);
    measurement.idle_difference = measurement.curr[3] - measurement.idle_prev;
    measurement.idle_prev = measurement.curr[3];
    measurement.total_time_difference = measurement.total_time_curr - measurement.total_time_prev;
    utilization = 100 * (1 - measurement.idle_difference / measurement.total_time_difference);
}  

std::string WorkerCoreCpu::getStartOutput(int index) {
    return "Core" + std::to_string(index);
}