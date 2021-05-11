cmake_minimum_required(VERSION 3.10)
project(solver VERSION 4)

add_compile_options(
    -std=c++17
    -O3
    -g
    -Wall
    -march=native
    -flto
)

include_directories(include)
# link_directories(/usr/lib/armadillo)
# link_libraries(armadillo)

add_executable(solver
    src/logger.cpp
    src/main.cpp
    src/network.cpp
    src/parse_functions.cpp
    src/parser.cpp
    src/timeseries.cpp
    # src/dynamicsystems.cpp
)