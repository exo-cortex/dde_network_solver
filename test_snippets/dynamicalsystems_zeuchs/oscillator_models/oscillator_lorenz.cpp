#pragma once

#include "./dynamicalsystem.cpp"

using namespace std;

struct stateLorenz {
	double x, y, z;
    stateLorenz(): x(1), y(1), z(1){};
	stateLorenz(double x, double y, double z): x(x), y(y), z(z) {};
};

class lorenzSystem : public dynamicalSystem<double> {
private:
    stateLorenz m_State;
    const double dt, sigma, beta, rho, kappa; // these are constants from m_Parameters. is it faster to store them here instead of using the map?
public:
    lorenzSystem(vector<double> &_history, map<const string, double> _p);
    void update();
	void printState();
	void writeState(ofstream& of);
};

lorenzSystem::lorenzSystem(vector<double> &_history, map<const string, double> _p)
: dynamicalSystem<double>(_history), dt(_p["dt"]), sigma(_p["sigma"]), beta(_p["beta"]), rho(_p["rho"]), kappa(_p["kappa"])
{
}

void lorenzSystem::update() {
    stateLorenz euler;
	advanceIterator();
    euler.x = sigma * (m_State.y - m_State.x) + kappa * *m_Delayed;
    euler.y = m_State.x * (rho - m_State.z) - m_State.y;
    euler.z = m_State.x * m_State.y - beta * m_State.z;
    m_State.x += dt * euler.x;
    m_State.y += dt * euler.y;
    m_State.z += dt * euler.z;
	*m_Delayed = m_State.x;
}

void lorenzSystem::printState(){
	cout << m_State.x << '\t' << m_State.y << '\t' << m_State.z << '\n';
}

void lorenzSystem::writeState(ofstream& of){
	of << setprecision(20) << m_State.x << '\t' << m_State.y << '\t' << m_State.z << '\n';
}
