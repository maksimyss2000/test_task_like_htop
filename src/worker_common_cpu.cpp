#include <numeric>
#include <iostream>

#include "worker_common_cpu.h"

void WorkerCommonCpu::calculateUsage(Measurement& measurement, float& utilization) {
    measurement.total_time_prev = measurement.total_time_curr;
    measurement.total_time_curr = std::accumulate(measurement.curr.begin(), measurement.curr.end(), 0);
    measurement.idle_difference = measurement.curr[3] - measurement.idle_prev;
    measurement.idle_prev = measurement.curr[3];
    measurement.total_time_difference = measurement.total_time_curr - measurement.total_time_prev;
    utilization = 100 * (1 - measurement.idle_difference / measurement.total_time_difference);
}  

std::string WorkerCommonCpu::getStartOutput(int index) {
    return "AVG";
}