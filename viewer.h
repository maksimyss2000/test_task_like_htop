#pragma once

#include <mutex>

class Viewer {
private:
    std::mutex print;
public:
    void printConsoleBuffer(std::string& start_str,float& utilization, int y_point, int x_point = 0);
    void updateConsole();
    Viewer();
    ~Viewer();
};