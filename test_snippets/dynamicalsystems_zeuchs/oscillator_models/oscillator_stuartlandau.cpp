#pragma once

#include <complex>
#include <cmath>

#include "./dynamicalsystem.cpp"

using namespace std;

struct stateStuartLandau {
	complex<double> z;
    stateStuartLandau(): z(1){};
	stateStuartLandau(double z): z(z) {};
};

class stuartLandauSystem : public dynamicalSystem<complex<double>> {
private:
    stateStuartLandau m_State;
    const double dt, lambda, omega, kappa; // these are constants from m_Parameters. is it faster to store them here 
    const complex<double> gamma;
    double time;
    // instead of using the map?
public:
    stuartLandauSystem(vector<complex<double>> &_history, map<const string, double> _p);
    void update();
	void printState();
	void writeState(ofstream& of);
    void writeAmplitude(ofstream& of);
};

stuartLandauSystem::stuartLandauSystem(vector<complex<double>> &_history, map<const string, double> _p)
: dynamicalSystem<complex<double>>(_history), 
dt(_p["dt"]), 
lambda(_p["lambda"]), omega(_p["omega"]), kappa(_p["kappa"]), 
gamma(_p["gammaRe"],_p["gammaIm"]),
time(0)
{
}

void stuartLandauSystem::update() 
{
    m_State.z += dt * ((lambda + 1i * omega + gamma * norm(m_State.z)) * m_State.z + kappa * *m_Delayed);
	*m_Delayed = m_State.z;
    time += dt;
	advanceIterator();
}

void stuartLandauSystem::printState(){
	cout << time << '\t' << m_State.z.real() << '\t' << m_State.z.imag() << '\n';
}

void stuartLandauSystem::writeState(ofstream& of){
	of << setprecision(12) << time << '\t' << m_State.z.real() << '\t' << m_State.z.imag() << '\n';
}

void stuartLandauSystem::writeAmplitude(ofstream& of){
    of << setprecision(12) << time << '\t' << abs(m_State.z) << '\n';
}