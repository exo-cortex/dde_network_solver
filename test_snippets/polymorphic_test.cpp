// #pragma once

#include <iostream>
#include <vector>
#include <iterator>
#include <complex>
#include <cmath>
#include <map>

using namespace std;

// abstract oscillator/dynamical systems class
class dynamicalSystem {
protected:
	vector<vector<complex<double>>>::iterator selfHistory;
	vector<vector<complex<double>>> &nodeHistory; // here: a vector of vectors, because delayed state AND delayed slope (derivative) have to be saved
	const map<const string, double> &systemParameters;
	
	void update();
	void advanceIterators();
public:
	dynamicalSystem(vector<vector<complex<double>>> &_history, map<const string, double> &_systemParameters)
	: nodeHistory(_history), systemParameters(_systemParameters)
	{
	};

};

class stuartLandau : public dynamicalSystem {
private:
	vector<complex<double>> state, k1, k2, k3, k4;
public:
	stuartLandau(vector<vector<complex<double>>> &history, map<const string, double> &systemParameters);
	void update();
};

stuartLandau::stuartLandau(vector<vector<complex<double>>> &history, map<const string, double> &systemParameters)
: dynamicalSystem(history, systemParameters)
{
}

void stuartLandau::update(){
	
}

int main(int argc, char* argv[]) {
vector<vector<complex<double>>> delayArray(1000, vector<complex<double>>(2,0));

map<const string, double> parametersStuartLandau {
	{"lambda", 0.123},
	{"omega", 1.0},
	{"gammaRe", 1.0},
	{"gammaIm", 1.0},
	{"inputG", 0.1}};

stuartLandau st(delayArray, parametersStuartLandau);

st.update();

}