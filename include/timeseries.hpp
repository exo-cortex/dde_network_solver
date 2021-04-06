#pragma once

#include <vector>
#include <fstream>

using namespace std;

struct uniqueEx {
	double value;
	unsigned int counts = 0;
};


class timeseries {
private:
	double stepSize;
	double globalMin, globalMax, globalAverage;
	double currentSegmentStart, currentSegmentEnd;
	vector<vector<double>> &currentSegment; // make ref? alternatively use this timeseries
	vector<uniqueEx> uniqueMin, uniqueMax;
	vector<ofstream> files;
public:
	timeseries(double _stepSize, double _currentSegmentStart, vector<vector<double>> _timeseries)
	: stepSize(_stepSize), currentSegmentStart(_currentSegmentStart), currentSegment(_timeseries) {
		currentSegmentEnd = currentSegmentStart + (double)currentSegment.size() * stepSize;
		globalMin = 0;
		globalMax = 0;
		globalAverage = 0;
	}

	void update(){
		currentSegmentStart = currentSegmentEnd;
		currentSegmentEnd += (double)currentSegment.size() * stepSize;
		analyseSegment();
	}

	void analyseSegment(){

	}

	// see old solver
	void checkMin();
	void checkMax();

	void simplifyWrite();
	void simplifyRecursive(vector<double>& segment);

};