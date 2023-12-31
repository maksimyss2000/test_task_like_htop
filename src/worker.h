#pragma once

#include <string>

#include "measurement.h"

class Worker {
public:
    virtual void calculateUsage(Measurement& curr, float& utilization) = 0;
    virtual std::string getStartOutput(int index = 0) = 0;
};

