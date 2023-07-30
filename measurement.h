#pragma once

#include <cstddef>
#include <array>

using  Measurement =  struct Measurement;

constexpr int COUNT_INDICATORS = 10;

struct Measurement {
    std::array<std::size_t, COUNT_INDICATORS> curr;
    float total_time_prev;
    float total_time_curr;
    float idle_prev;
    float idle_difference;
    float total_time_difference;
    float utilization; 
    Measurement() {
        float total_time_curr = 0;
        float idle_prev = 0;
    }  
};