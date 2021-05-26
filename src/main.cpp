#include <iostream>
// #include <chrono>
#include <cmath>
#include <filesystem>
#include <map>

#include "../include/logger.hpp"
#include "../include/constants.hpp"
#include "../include/network.hpp"
#include "../include/timeseries.hpp"

#include "../include/parse_functions.hpp"
// #include "../include/dynamicsystems.hpp"

using namespace std;
namespace fs = std::filesystem;

// ++++++++++++++++++++++++++++++++
// this has to dissappear later
const double INVERSE_DT = 1 * 64.0; // how many integration-steps per time unit (e.g. [s])
double STEPSIZE = 1.0 / INVERSE_DT;
bool WRITE_TIMESERIES = true;
string MAIN_DIRECTORY_PATH = "../test_data";
// ++++++++++++++++++++++++++++++++

structlog LOGCFG = {};

int main(int argc, char *argv[]) 
{
	LOGCFG.level = WARN;

	// stuff that will later be done somewhere else
	fs::create_directories(MAIN_DIRECTORY_PATH);
	
	map<const string, double> parametersStuartLandau {
	{"lambda", 0.123},
	{"omega", 1.0},
	{"gammaRe", 1.0},
	{"gammaIm", 1.0},
	{"inputG", 0.1}};

	readParameters(parametersStuartLandau, argc, argv);


	network net(9, "ring");
	net.setDefaults(10, 0.08, 0.25);
	net.putRing();

	net.nextEdgeGroup("jumps");
	net.setDefaults(100, 0.1, 0.35);
	net.putJumps(4,2);
	net.nextEdgeGroup("randomJump");
	net.setDefaults(33, 0.05, 0.125);
	net.putEdge(3, 8);

	net.randomizeWeights(0.01, 0);
	net.randomizePhase(0.01, 1);
	net.randomizeDelay(0.01, 2);

	net.printNetwork();
}