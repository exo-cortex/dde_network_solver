#include <iostream>
#include <chrono>
#include <cmath>

#include "../include/constants.hpp"
#include "../include/network.hpp"
// #include "../include/parser.hpp"
#include "../include/timeseries.hpp"

using namespace std;

const double INVERSE_DT = 64.0;
double STEPSIZE = 1.0 / INVERSE_DT;
bool WRITE_TIMESERIES = true;
string DIRECTORY_PATH = "./";

int main(int argc, char *argv[]) 
{

	uint numOsc = 1;
	// uint timeseriesSize = 1000;
	
	timeseries ts(numOsc, 2.0);

	// ts.analyseSegment();
	ts.simplifyWrite();



}