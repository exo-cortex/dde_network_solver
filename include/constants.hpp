#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <random>

// using namespace std;

extern const double INVERSE_DT;
extern double STEPSIZE;

extern std::vector<std::mt19937> NETWORK_RANDOM_NUMBER_GENERATOR;
extern std::uniform_real_distribution<double> UNIFORM_SYMMETRIC;
extern std::uniform_real_distribution<double> UNIFORM;

// directory that results are stored in
extern std::string MAIN_DIRECTORY_PATH;

// files
extern std::vector<std::ofstream> TIMESERIES_FILES;

// switches
extern bool WRITE_TIMESERIES;