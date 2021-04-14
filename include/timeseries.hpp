#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cmath>

#include <filesystem>

using namespace std;

struct uniqueEx {
	double value;
	unsigned int counts = 0;
};

class timeseries {
private:
	// const double stepSize = 0.01;
	const uint numOscillators;
	const double segmentLength; 

	vector<vector<double>> segment; // make ref? alternatively use this timeseries
	const uint segmentSize;
	double globalMin, globalMax, globalAverage;
	double segmentStart, segmentEnd;
	vector<double> almostLastElement, lastElement;
	vector<uniqueEx> uniqueMin, uniqueMax;

public:

	timeseries(uint _numOscillators, double _segmentStart, double _segmentLength);
	~timeseries();

	void create_test_segment();


	void openTimeseriesFiles(string _filename);
	void closeTimeseriesFiles(); // move into descructor ?

	void update();

	void analyseSegment();

	// see old solver
	void checkMin();
	void checkMax();

	void simplifyWrite();
	void simplifyRecursive(vector<double> &subSegment, ofstream& traceOutStream, uint begin, uint end, double _epsilon);

};