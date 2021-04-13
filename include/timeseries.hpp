#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
// #include <experimental/filesystem>


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
	double segmentStart, segmentEnd;
	double globalMin, globalMax, globalAverage;

	vector<vector<double>> segment; // make ref? alternatively use this timeseries
	const uint segmentSize;
	vector<double> almostLastElement, lastElement;
	vector<uniqueEx> uniqueMin, uniqueMax;

	// vector<ofstream> &files;
public:

	timeseries(uint _numOscillators, double _segmentLength);
	void openTimeseriesFiles();
	void closeTimeseriesFiles();

	void update();

	void analyseSegment();

	// see old solver
	void checkMin();
	void checkMax();

	void simplifyWrite();
	void simplifyRecursive(vector<double> &subSegment, ofstream& traceOutStream, uint begin, uint end, double _epsilon);

};