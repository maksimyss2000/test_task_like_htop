#include <ncurses.h>                       /* this library isn't thread safe */
#include <iostream>
#include "viewer.h"

void Viewer::updateConsole() {
    refresh();
}

void Viewer::printConsoleBuffer(std::string& start_str,float& utilization,int y_point, int x_point) {
    mvprintw(y_point, x_point ,"%15s : %5.2f%%  ", start_str.c_str(), utilization);
}

Viewer::Viewer() {
    initscr();
    curs_set(0);
}

Viewer::~Viewer() {
    endwin();
}