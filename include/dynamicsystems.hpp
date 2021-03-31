#include <iostream>
// #include <array>
#include <vector>
#include <complex>
#include <cmath>

usin namespace std;

class stuartlandau {
private:
	const double m_lambda, m_omega, m_gammaRe, m_gammaIm;
	double *inputPerturbation;

	complex<double> m_state, m_slope, m_inputSum, m_inputSlope;
	complex<double> m_k1, m_k2, m_k3, m_k4;

	vector<vector<complex<double>>> &history;
public:

	stuartlandau(const double& _lambda, );

	void initialize();

	void updateState();





}


// class oscillator {
// private:
// 	const double m_lambda, m_omega, m_gammaReal, m_gammaImag;
	
// 	complex<double> m_state;
// 	complex<double> m_dState, inputSum, inputDState
// 	complex<double> m_k1, m_k2, m_k3, m_k4;
// 	array<array<complex<double>>> &history;


// 	// initialization methods
// 	void initialState(array<double> &history);


// 	void updateState();


// public:
// 	oscillator(const double &_lambda, const double &m_omega, const double &m_gammaReal, const double &m_gammaImag);
// }

