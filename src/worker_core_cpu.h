#pragma once

#include "worker.h"

class WorkerCoreCpu : public Worker {
public:
    void calculateUsage(Measurement& curr, float& utilization) override;
    std::string getStartOutput(int index = 0) override;
};
