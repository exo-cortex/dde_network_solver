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

extern std::string DIRECTORY_PATH;


// switches
extern bool WRITE_TIMESERIES;
extern std::vector<std::ofstream> TIMESERIES_FILES;