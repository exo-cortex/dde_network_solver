#pragma once

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
	const map<string, double> &systemParameters;

	void update();
	void advanceIterators();
public:
	dynamicalSystem(vector<vector<complex<double>>> &history, map<string, double> &systemParameters);

};

// class nodeStuartLandau {
// 	struct stateStuartLandau {
// 		complex<double> z;
// 	};
// 	stateStuartLandau state, slope;
// 	const double lambda, omega, gammaRe, gammaIm, gInput;
	
// };

// class nodeLangKobayashi {
// 	struct stateLangKobayashi {
// 		complex<double> e;
// 		double n;
// 	};
// 	stateLangKobayashi state, slope;
// 	vector<vector<complex<double>>> &historyLangKobayashi;
// 	stateLangKobayashi state;
// 	// example
// 	const double alpha;
// 	const double decayTime;
// };

// class nodeMDRE {
// 	struct stateMDRE {
// 		complex<double> E;
// 		double rho_GS_e_act;
// 		double rho_GS_h_act;
// 		double rho_GS_e_inact;
// 		double rho_GS_h_inact;
// 		double rho_ES_e;
// 		double rho_ES_h;
// 		double w_e;
// 		double w_h;
// 	};
// 	stateMDRE state, slope;
// 	// const double constants;

// };

// class stuartlandau {
// private:

// 	vector<complex<double>>::const_iterator inIt;
// 	vector<complex<double>>::iterator it;

// 	const double m_lambda, m_omega, m_gammaRe, m_gammaIm, m_gInput;
// 	complex<double> m_state, m_slope, m_inputSum, m_inputSumSlope;

// 	vector<vector<complex<double>>> &history;
// 	void advanceIterator();

// public:

// 	stuartlandau(vector<complex<double>> &history);
// 	// initialization methods
// 	void init();
// 	void initHistory(vector<complex<double>> &stateHistory);

// 	void updateState();

// };

