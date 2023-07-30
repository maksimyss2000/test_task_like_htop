#pragma once

#include "worker.h"

class WorkerCommonCpu : public Worker {
public:
    void calculateUsage(Measurement& curr) override;
    std::string getStartOutput(int index = 0) override;
};
