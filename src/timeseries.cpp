
#include "../include/timeseries.hpp"

using namespace std;

struct point {
	double x, y;
	point(double x, double y): x(x), y(y){};
	point(vector<double> p): x(p[0]), y(p[1]){};
};

double perpendicularDistance(point P, point A, point B){
	return abs((B.y - A.y) * P.x - (B.x - A.x) * P.y + B.x * A.y - B.y * A.x) / sqrt(pow(B.y - A.y,2) + pow(B.x - A.x,2));

};

void timeseries::simplifyWrite(){
	for (vector<double> &s : currentSegment){
		// simplifyRecursive();
	}
};

void timeseries::simplifyRecursive(vector<double>& segment){

	double maxDistance = 0;
	uint index = 0;
	uint end = segment.size() - 1;
	for (uint i = 1; i <= end; i++){
		// double d = perpendicularDistance(P, A, B);

	}


}