#include <iostream>
#include <chrono>

#include "../include/network.hpp"
#include "../include/parser.hpp"
#include "../include/timeseries.hpp"
// #include "../include/constants.hpp"

using namespace std;

int main(int argc, char *argv[]) 
{

	// construct example network 
	network net(7); // network with 7 nodes
	net.setDefaults(100, 1, 0); // set edge-defaults [coupling-delay=100, coupling-strength=1.0, coupling-phase=0.0] 
	net.putEdge(1,0, 100, 0.1, 0); // create an edge [1]<-[0] with delay=100, strength=0.1, phase=0.0
	net.setEdgeGroup(1); // set/change edge-group to 1 (default is 0)
	net.putRing(); // add a ring
	net.printNetwork();

	vector<vector<double>> segment(1000, vector<double>(0,1));

	timeseries ts(0.01, 0, segment);


}
