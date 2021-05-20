#pragma once

#include <complex>
#include <cmath>

#include "./dynamicalsystem.cpp"

using namespace std;

struct stateLangKobayashi {
	complex<double> E;
    double n;
    stateLangKobayashi(): E(1.0), n(0.1){};
	stateLangKobayashi(double E, double n): E(E), n(n) {};
};

class langKobayashiSystem : public dynamicalSystem<complex<double>> {
private:
    stateLangKobayashi m_State;
    const double dt, alpha, P, T_LK;// these are constants from m_Parameters. is it faster to store them here instead of using the map?
    complex<double> kappaphi;
public:
    langKobayashiSystem(vector<complex<double>>& _history, map<const string, double> _p);
    void update();
	void printState();
	void writeState(ofstream& of);
    void writeAmplitude(ofstream& of);
};

langKobayashiSystem::langKobayashiSystem(vector<complex<double>>& _history, map<const string, double> _p)
: dynamicalSystem<complex<double>>(_history),
dt(_p["dt"]), 
alpha(_p["alpha"]), 
P(_p["P"]), 
T_LK(_p["T_LK"]), 
kappaphi(_p["kappa"] * exp(1i * 2.0 * M_PI * _p["phi"]))
{
}

void langKobayashiSystem::update() {
    stateLangKobayashi euler;
	advanceIterator();
    time += dt;
    euler.E = (1.0 + 1i * alpha) * m_State.n * m_State.E + kappaphi * *m_Delayed;
    euler.n = (1 / T_LK) * (P - m_State.n - (2 * m_State.n + 1)*norm(m_State.E));
    m_State.E += dt * euler.E;
    m_State.n += dt * euler.n;
	*m_Delayed = m_State.E;
}

void langKobayashiSystem::printState() {
	cout << time << '\t' << m_State.E.real() << '\t' << m_State.E.imag() << '\t' << m_State.n << '\n';
}

void langKobayashiSystem::writeState(ofstream& of) {
	of << setprecision(20) << time << '\t' << m_State.E.real() << '\t' << m_State.E.imag() << '\t' << m_State.n << '\n';
}

void langKobayashiSystem::writeAmplitude(ofstream& of) {
    of << setprecision(20) << time << '\t' << abs(m_State.E) << '\t' << m_State.n << '\n';
}
