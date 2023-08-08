#include <iostream>
#include <cassert>
#include <cmath>
#include <ncurses.h>                       /* this library isn't thread safe */

#include "viewer.h"

constexpr int COUNT_COLUMN = 3;
constexpr int WIDHT_COLUMN = 20;
constexpr int GRAPH_OFFSET_Y = 3;
constexpr int GRAPH_OFFSET_X = 8;
constexpr int MAX_HEIGHT_SIZE_GRAPH = 26;
constexpr int MAX_WIDHT_SIZE_GRAPH = 50;
constexpr int WIDTH_BAR = 2;

void Viewer::updateConsole() {
    refresh();
    clear();
}

void Viewer::printConsoleBuffer(std::string& start_str, float& utilization, int index_threads) {
    int x_point = (index_threads / height_column) * WIDHT_COLUMN;
    int y_point = index_threads % height_column;
    mvprintw(y_point, x_point,"%6s:%6.2f%% ", start_str.c_str(), utilization);
}

/* ncurses has inbuilt methods box(), but they break when the console size changes */
void Viewer::printGraphBox() {
    mvvline(upper_left_graph_corner_y - 1, upper_left_graph_corner_x - 1,  '|', height_graph + 1);
    mvvline(upper_left_graph_corner_y - 1, upper_left_graph_corner_x + widht_graph + 1, '|', height_graph + 1);

    mvhline(upper_left_graph_corner_y - 2, upper_left_graph_corner_x ,  '-', widht_graph  + 1);
    mvhline(upper_left_graph_corner_y + height_graph , upper_left_graph_corner_x ,  '-', widht_graph + 1);

    mvprintw(upper_left_graph_corner_y - 2,upper_left_graph_corner_x -1, "+");
    mvprintw(upper_left_graph_corner_y - 2,upper_left_graph_corner_x + widht_graph + 1, "+");
    mvprintw(upper_left_graph_corner_y  + height_graph,upper_left_graph_corner_x -1, "+");
    mvprintw(upper_left_graph_corner_y  + height_graph,upper_left_graph_corner_x + widht_graph + 1, "+");
}

int Viewer::mod(int val, int m) {
    int res = val % m;
    if (res < 0)
        res = res + m;
    return res;
}

void Viewer::printLabels(std::string& graph_name) {
    mvprintw(upper_left_graph_corner_y - 1, upper_left_graph_corner_x + (widht_graph - graph_name.size()),"%s", graph_name.c_str());
    
    mvprintw(upper_left_graph_corner_y, upper_left_graph_corner_x - 5, "100%%"); 
    mvprintw(upper_left_graph_corner_y + (height_graph / 2), upper_left_graph_corner_x - 5, "%.0f%%", 100 - (height_graph / 2) * delta_y);        
    mvprintw(upper_left_graph_corner_y + (height_graph - 2), upper_left_graph_corner_x - 5, "%.0f%%", 2 * delta_y);        
}

void Viewer::printGraph(std::string& graph_name, Data<float>& samples, int index_start) {  
    printGraphBox();
    printLabels(graph_name);    
    int size = samples.getSize();
    for(int i = 0;i < count_bars; i++) {
        int hight_bar = round(samples[mod((index_start - i), size)] / delta_y);
        for (int j = 0; j < WIDTH_BAR; j++) {
            mvvline(upper_left_graph_corner_y + (height_graph - hight_bar), 
                    upper_left_graph_corner_x + i * 2 + j ,
                    '#', hight_bar);
        }
    }
}

void Viewer::setGraphParameters(int count_samples) {
    if (count_samples * WIDTH_BAR <= MAX_WIDHT_SIZE_GRAPH) {
        widht_graph = count_samples * WIDTH_BAR;
        count_bars = count_samples;
    } else {
        widht_graph = MAX_WIDHT_SIZE_GRAPH * WIDTH_BAR;
        count_bars = MAX_WIDHT_SIZE_GRAPH / WIDTH_BAR;
    }
    height_graph = MAX_HEIGHT_SIZE_GRAPH;
    delta_y = 100.0 / height_graph;

    upper_left_graph_corner_y = height_column + GRAPH_OFFSET_Y;
    upper_left_graph_corner_x = GRAPH_OFFSET_X;
}

void Viewer::setUsedParameters(int count_threads, int count_samples) {
    this->count_threads = count_threads;
    height_column = (count_threads + 1) / COUNT_COLUMN;
    setGraphParameters(count_samples);
}

Viewer::Viewer() {
    initscr();
    curs_set(0);
}

Viewer::~Viewer() {
    endwin();   
}