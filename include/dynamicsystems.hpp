#include <iostream>
#include <vector>
#include <iterator>
#include <complex>
#include <cmath>
#include <map>

usin namespace std;

class stuartlandau {
private:

	vector<complex<double>>::const_iterator it;

	const double m_lambda, m_omega, m_gammaRe, m_gammaIm, m_gInput;
	complex<double> m_state, m_slope, m_inputSum, m_inputSumSlope;

	vector<vector<complex<double>>> &history;
	advanceIterator();

public:

	stuartlandau(array<double>);
	// initialization methods
	void init();
	void initHistory(vector<complex<double>> &stateHistory);

	void updateState();

};

