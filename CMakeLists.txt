cmake_minimum_required(VERSION 2.6)

project(hash_server)

set(SRC_DIR src)
set(SOURCES ${SRC_DIR}/data_miner.cpp  ${SRC_DIR}/htop.cpp  ${SRC_DIR}/main.cpp  ${SRC_DIR}/viewer.cpp  ${SRC_DIR}/worker_common_cpu.cpp ${SRC_DIR}/worker_core_cpu.cpp)

add_executable(htop.out ${SOURCES})

target_link_libraries(htop.out ncurses)