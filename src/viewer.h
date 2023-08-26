#pragma once

#include "data.h"

#include <string>
#include <ncurses.h>

class Viewer {
private:
    int count_bars;
    int widht_graph;
    int height_graph;
    int height_column;
    int count_threads;
    int upper_left_graph_corner_x;
    int upper_left_graph_corner_y;
    float delta_y;
    int mod(int val, int m);
    void printLabels(std::string& graph_name);
    void printGraphBox();
    void setGraphParameters(int count_samples);
public:
    Viewer();
    ~Viewer();
    void updateConsole();
    void setUsedParameters(int count_threads,int count_samples);
    void printGraph(std::string& output, Data<float>& samples,int index_start);
    void printConsoleBuffer(std::string& start_str, float& utilization, int index_threads);
};