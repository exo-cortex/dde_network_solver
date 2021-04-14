#include "../include/constants.hpp"
#include "../include/timeseries.hpp"

using namespace std;

vector<ofstream> TIMESERIES_FILES;

struct point {
	double x, y;
	point(double x, double y): x(x), y(y){};
	point(vector<double> p): x(p[0]), y(p[1]){};
};

double perpendicularDistance(point P, point A, point B){
	return abs((B.y - A.y) * P.x - (B.x - A.x) * P.y + B.x * A.y - B.y * A.x) / sqrt( pow(B.y - A.y,2) + pow(B.x - A.x,2) );
}

timeseries::timeseries(uint _numOscillators, double _segmentStart, double _segmentLength)
	: 
	numOscillators(_numOscillators),
	segmentLength(_segmentLength),
	segment(vector<vector<double>>(numOscillators, vector<double>(INVERSE_DT * _segmentLength, 0))),
	segmentSize(segment[0].size()),
	globalMin(0),
	globalMax(0),
	globalAverage(0),
	segmentStart(_segmentStart),
	segmentEnd(segmentStart + _segmentLength)
{

	openTimeseriesFiles("ts_");

	// very ugly - testing - remove later...
	create_test_segment();
}

timeseries::~timeseries(){
	closeTimeseriesFiles();
}

void timeseries::create_test_segment(){
	double some_number = 0;
	for (uint count = 0; count < 4; count++){
		for (vector<double> &sub : segment){
			for (uint si = 0; si < sub.size(); si++){
				sub[si] = pow(cos(some_number * 0.00123 + cos(some_number * 0.01)), 8) * pow(cos(some_number * 0.0321), 15);
				some_number += STEPSIZE;
			}
		}
		simplifyWrite();
		segmentStart = segmentEnd;
		segmentEnd += segmentLength;
	}
}

void timeseries::openTimeseriesFiles(string _filename = "timeseries_"){
	if (WRITE_TIMESERIES){
		for (uint i = 0; i < numOscillators; ++i){
			string fileName = MAIN_DIRECTORY_PATH + '/' + _filename + to_string(i) + ".txt";
			TIMESERIES_FILES.emplace_back(ofstream{ fileName });
		}
	}
}

void timeseries::closeTimeseriesFiles(){
	for (uint i = 0; i < numOscillators; ++i){
		TIMESERIES_FILES[i].close();
	}
}

void timeseries::update(){
	segmentStart = segmentEnd;
	segmentEnd += (double)segment.size() * STEPSIZE;
	analyseSegment();
}

void timeseries::analyseSegment(){
}

void timeseries::simplifyWrite(){
	for (uint i = 0; i < numOscillators; ++i){
		simplifyRecursive(segment[i], TIMESERIES_FILES[i], 0, segmentSize - 1, 0.0001);
		// for (uint t = 0; t < segment[i].size(); +{
		// 	TIMESERIES_FILES[i] << segmentStart + (double)t * STEPSIZE << '\t' << segment[i][t] << '\n';
		// }
	}
}

void timeseries::simplifyRecursive(vector<double> &subSegment, ofstream &traceOutStream, uint _begin, uint _end, double _epsilon){
	double maxDistance = 0;
	uint maxDistanceIndex = _begin + 1;

	point A = point(segmentStart + (double)_begin * STEPSIZE, subSegment[_begin]);
	point B = point(segmentStart + (double)_end * STEPSIZE, subSegment[_end]);
	traceOutStream << A.x << '\t' << A.y << '\n';

	for (uint pIndex = _begin + 1; pIndex < _end; pIndex++){
		point p = point(segmentStart + (double)pIndex * STEPSIZE, subSegment[pIndex]);
		double d = perpendicularDistance(p, A, B);
		if (d > maxDistance) {
			maxDistance = d;
			maxDistanceIndex = pIndex;
		}
	}

	if (maxDistance > _epsilon){
		simplifyRecursive(subSegment, traceOutStream, _begin, maxDistanceIndex, _epsilon);
		simplifyRecursive(subSegment, traceOutStream, maxDistanceIndex, _end, _epsilon);
		return;
	}

	traceOutStream << B.x << '\t' << B.y << '\n';
	return;
}