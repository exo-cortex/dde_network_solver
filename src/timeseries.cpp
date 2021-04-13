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
	return abs((B.y - A.y) * P.x - (B.x - A.x) * P.y + B.x * A.y - B.y * A.x) / sqrt(pow(B.y - A.y,2) + pow(B.x - A.x,2));
}

timeseries::timeseries(uint _numOscillators, double _segmentLength)
: numOscillators(_numOscillators), segmentLength(_segmentLength), segment(vector<vector<double>>(numOscillators, vector<double>(INVERSE_DT * _segmentLength, 0))), segmentSize(segment[0].size())
{
	globalMin = 0;
	globalMax = 0;
	globalAverage = 0;
	openTimeseriesFiles();
	closeTimeseriesFiles();

	double some_number = 0;
	for (vector<double> &sub : segment){
		for (uint si = 0; si < sub.size(); si++){
			sub[si] = cos(some_number) * cos(some_number * 0.123);
			some_number += 0.321;
			// cout << d << ' ';
		}
		// cout << some_number << endl;
	}

	for (double &d : segment[0]){
		cout << d << ' ';
	}
}

void timeseries::openTimeseriesFiles(){
	if (WRITE_TIMESERIES){
		for (uint i = 0; i < numOscillators; ++i){
			string fileName = DIRECTORY_PATH + "text " + to_string(i) + ".txt";
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
	segmentStart = segmentEnd + STEPSIZE;
	segmentEnd += (double)segment.size() * STEPSIZE;
	analyseSegment();
}

void timeseries::analyseSegment(){
}

void timeseries::simplifyWrite(){
	for (uint i = 0; i < numOscillators; ++i){
		
		// cout << "segment size of segment " << i << " = " << segment[i].size() << "   segment size = " << segment.size() << '\n';
		simplifyRecursive(segment[i], TIMESERIES_FILES[i], 0, segmentSize, 0.01);
	}
}


void timeseries::simplifyRecursive(vector<double> &subSegment, ofstream &traceOutStream, uint _begin, uint _end, double _epsilon){
	double maxDistance = 0;

	uint maxDistanceIndex = _begin + 1;
	uint end = _end - 1;

	point A = point(segmentStart, subSegment[0]);
	point B = point(segmentEnd, subSegment[_end]);

	for (uint pIndex = _begin + 1; pIndex <= _end - 1; pIndex++){

		point p = point(segmentStart + (double)pIndex * STEPSIZE, subSegment[pIndex]);

		double d = perpendicularDistance(p, A, B);
		// cout << d << "\n";
		if (d > maxDistance) {

			maxDistance = d;
			maxDistanceIndex = pIndex;

		}
	}
	if (maxDistance > _epsilon){

		cout << "subdivision [" << _begin << "-" << maxDistanceIndex << "] [" << maxDistanceIndex << "-" << _end << "].\n";

		simplifyRecursive(subSegment, traceOutStream, _begin, maxDistanceIndex, _epsilon);
		simplifyRecursive(subSegment, traceOutStream, maxDistanceIndex, _end, _epsilon);
	}
	else {
		traceOutStream << A.x << '\t' << A.y << '\n';
		traceOutStream << B.x << '\t' << B.y << '\n';
	}

}