#include <iostream>
#include <chrono>
#include <cmath>
#include <filesystem>

#include "../include/constants.hpp"
#include "../include/network.hpp"
// #include "../include/parser.hpp"
#include "../include/timeseries.hpp"

using namespace std;


// ++++++++++++++++++++++++++++++++
// this has to dissappear later
const double INVERSE_DT = 1 * 64.0;
double STEPSIZE = 1.0 / INVERSE_DT;
bool WRITE_TIMESERIES = true;
string MAIN_DIRECTORY_PATH = "../test_data";
// ++++++++++++++++++++++++++++++++


int main(int argc, char *argv[]) 
{

	filesystem::create_directories(MAIN_DIRECTORY_PATH);

	uint numOsc = 1;
	// uint timeseriesSize = 1000;
	
	timeseries ts(numOsc, 0, 1000.0);

	// ts.analyseSegment();
	// ts.simplifyWrite();
	// cout << '\n';


}