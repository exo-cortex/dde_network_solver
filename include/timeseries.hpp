#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

struct uniqueEx {
	double value;
	unsigned int counts = 0;
};


class timeseries {
private:
	double stepSize;
	double globalMin, globalMax, globalAverage;
	double segmentStart, segmentEnd;
	vector<vector<double>> &segment; // make ref? alternatively use this timeseries
	vector<uniqueEx> uniqueMin, uniqueMax;
	vector<ofstream> files;
public:
	timeseries(double _stepSize, double _segmentStart, vector<vector<double>> &_timeseries);

	void update();

	void analyseSegment();

	// see old solver
	void checkMin();
	void checkMax();

	void simplifyWrite();
	void simplifyRecursive(vector<double> &subSegment, uint begin, uint end);

};