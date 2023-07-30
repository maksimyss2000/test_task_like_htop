#pragma once

#include "measurement.h"
#include "data.h"

class DataMiner {
public:
    void updateData(Data<Measurement>& measurements);
};