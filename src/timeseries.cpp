#include "../include/timeseries.hpp"

using namespace std;

struct point {
	double x, y;
	point(double x, double y): x(x), y(y){};
	point(vector<double> p): x(p[0]), y(p[1]){};
};

double perpendicularDistance(point P, point A, point B){
	return abs((B.y - A.y) * P.x - (B.x - A.x) * P.y + B.x * A.y - B.y * A.x) / sqrt(pow(B.y - A.y,2) + pow(B.x - A.x,2));
}

timeseries::timeseries(double _stepSize, double _segmentStart, vector<vector<double>> &_timeseries)
: stepSize(_stepSize), segmentStart(_segmentStart), segment(_timeseries) {
	segmentEnd = segmentStart + (double)segment.size() * stepSize;
	globalMin = 0;
	globalMax = 0;
	globalAverage = 0;
}

void timeseries::update(){
	segmentStart = segmentEnd + stepSize;
	segmentEnd += (double)segment.size() * stepSize;
	analyseSegment();
}

void timeseries::analyseSegment(){
}

void timeseries::simplifyWrite(){
	for (vector<double> &s : segment){
		simplifyRecursive(s, 0, s.size());
	}
}

void timeseries::simplifyRecursive(vector<double> &subSegment, uint _begin, uint _end){

	double maxDistance = 0;
	uint maxDistanceIndex = _begin;
	uint end = _end - 1;
	point A = point(segmentStart, subSegment[0]);
	point B = point(segmentEnd, subSegment[end]);
	for (uint pIndex = 1; pIndex < end; pIndex++){
		point p = point(segmentStart + (double)pIndex * stepSize, subSegment[pIndex]);
		double d = perpendicularDistance(p, A, B);
		if (d > maxDistance) {
			maxDistance = d;
			maxDistanceIndex = pIndex;
		}
	}
}