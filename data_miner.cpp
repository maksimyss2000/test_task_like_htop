#include <fstream>

#include "data_miner.h" 

void DataMiner::updateData(Data<Measurement>& measurements) {
    std::ifstream proc_stat("/proc/stat");
    for (auto iter = measurements.begin(); iter != measurements.end(); iter++) {
        proc_stat.ignore(5, ' ');
        for (auto& elem : (*iter).curr) {
            proc_stat >> elem;
        }           
    }
}
