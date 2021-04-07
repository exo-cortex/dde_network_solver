#include <iostream>
#include <chrono>
#include <cmath>

#include "../include/network.hpp"
#include "../include/parser.hpp"
#include "../include/timeseries.hpp"
// #include "../include/constants.hpp"

using namespace std;

int main(int argc, char *argv[]) 
{

	vector<vector<double>> segment(2, vector<double>(10,0));

	cout << "segments = " << segment.size() << endl;
	cout << "subsegment length = " << segment[0].size() << endl;

	double wert = 0;
	for (vector<double> &s : segment){
		for (double &d : s){
			d = sin(wert * 2.0 * M_PI);
			wert += 0.01;
			// cout << d << endl;
		}
	}

	timeseries ts(0.01, 0, segment);
	// ts.analyseSegment();
	ts.simplifyWrite();
}
