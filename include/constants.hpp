#pragma once

#include <iostream>
#include <vector>
#include <random>

using namespace std;

// global constants

vector<mt19937> NETWORK_RANDOM_NUMBER_GENERATOR(4);
uniform_real_distribution<double> UNIFORM_SYMMETRIC(-1,1);
uniform_real_distribution<double> UNIFORM(0,1);