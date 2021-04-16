#include <iostream>
// #include <chrono>
#include <cmath>
#include <filesystem>

#include "../include/constants.hpp"
#include "../include/network.hpp"
// #include "../include/parser.hpp"
#include "../include/timeseries.hpp"
#include "../include/dynamicsystems.hpp"

using namespace std;


// ++++++++++++++++++++++++++++++++
// this has to dissappear later
const double INVERSE_DT = 1 * 64.0; // how many integration-steps per time unit (e.g. [s])
double STEPSIZE = 1.0 / INVERSE_DT;
bool WRITE_TIMESERIES = true;
string MAIN_DIRECTORY_PATH = "../test_data";
// ++++++++++++++++++++++++++++++++


int main(int argc, char *argv[]) 
{

	// stuff that will later be done somewhere else
	filesystem::create_directories(MAIN_DIRECTORY_PATH);

	uint numOsc = 1;
	
	timeseries ts(numOsc, 0, 1000.0);

	// ts.simplifyWrite();

}