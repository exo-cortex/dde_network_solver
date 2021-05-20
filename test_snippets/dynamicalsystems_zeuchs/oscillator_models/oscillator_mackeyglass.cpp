#pragma once

#include <cmath>

#include "./dynamicalsystem.cpp"

using namespace std;

struct stateMackeyGlass {
	double p;
	stateMackeyGlass(): p(0.01){};
	stateMackeyGlass(double p): p(p) {};
};

class mackeyGlassSystem : public dynamicalSystem<double> {
private:
	stateMackeyGlass m_State;
	const double dt, beta0, theta, n, gamma; // these are constants from m_Parameters. is it faster to store them here instead of using the map?
	double keepstate;
public:
	mackeyGlassSystem(vector<double> &_history, map<const string, double> _p);
	void update();
	void printState();
	void writeState(ofstream& of);
	void writeParametricState(ofstream& of);
};

mackeyGlassSystem::mackeyGlassSystem(vector<double> &_history, map<const string, double> _p)
: dynamicalSystem<double>(_history), 
dt(_p["dt"]), beta0(_p["beta0"]), theta(_p["theta"]), n(_p["n"]), gamma(_p["gamma"])
{
}

void mackeyGlassSystem::update() {
	advanceIterator();
	time += dt;
	// m_State.p += dt * ((beta0 * pow(theta, n)) / (pow(theta, n) - pow(*m_Delayed,n)) - gamma * m_State.p) ;
	m_State.p += dt * ((beta0 * *m_Delayed) / (1 + pow(*m_Delayed,n)) - gamma * m_State.p);
	keepstate = *m_Delayed;
	*m_Delayed = m_State.p;
}

void mackeyGlassSystem::printState(){
	cout << m_State.p << '\t' << *m_Delayed << '\n';
}

void mackeyGlassSystem::writeState(ofstream& of){
	// of << setprecision(20) << time << '\t' << m_State.p << '\n';
	of << setprecision(12) << m_State.p << '\n';
}

void mackeyGlassSystem::writeParametricState(ofstream& of){
	// of << setprecision(20) << time << '\t' << m_State.p << '\n';
	of << setprecision(12) << time << '\t' << m_State.p << '\t' << keepstate << '\n';
}