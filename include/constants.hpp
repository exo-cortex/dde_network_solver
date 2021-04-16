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

// physical constants

namespace physical {
    const double e    = 1.6021766208e-19;		// elementary charge in C
    const double hbar = 6.582119514e-13;		// Planck constant in meVs
    const double kB   = 8.6173303e-2;			// Boltzmann constant in meVK⁻¹
    const double m0   = 9.10938356e-31;		// electron mass in kg
    const double me   = 0.043 * m0;			// effective electron mass in kg
    const double mh   = 0.45 * m0;			// effective hole mass in kg
}