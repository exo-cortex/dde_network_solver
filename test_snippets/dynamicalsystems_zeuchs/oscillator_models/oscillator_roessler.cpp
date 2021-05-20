#pragma once

#include "./dynamicalsystem.cpp"

using namespace std;

struct stateRoessler {
	double x, y, z;
    stateRoessler(): x(1), y(1), z(1){};
	stateRoessler(double x, double y, double z): x(x), y(y), z(z) {};
};

class roesslerSystem : public dynamicalSystem<double> {
private:
    stateRoessler m_State;
    const double dt, a, b, c; // these are constants from m_Parameters. is it faster to store them here instead of using the map?
public:
    roesslerSystem(vector<double> &_history, map<const string, double> _p);
    void update();
	void printState();
	void writeState(ofstream& of);
};

roesslerSystem::roesslerSystem(vector<double> &_history, map<const string, double> _p)
: dynamicalSystem<double>(_history), dt(_p["dt"]), a(_p["a"]), b(_p["b"]), c(_p["c"])
{
}

void roesslerSystem::update() {
    stateRoessler euler;
	// advanceIterator();
    euler.x = -m_State.y - m_State.z;
    euler.y = m_State.x + a * m_State.y;
    euler.z = b + m_State.z * (m_State.x - c);
    m_State.x += dt * euler.x;
    m_State.y += dt * euler.y;
    m_State.z += dt * euler.z;
	// *m_Delayed = m_State.x;
}

void roesslerSystem::printState(){
	cout << m_State.x << '\t' << m_State.y << '\t' << m_State.z << '\n';
}

void roesslerSystem::writeState(ofstream& of){
	of << setprecision(20) << m_State.x << '\t' << m_State.y << '\t' << m_State.z << '\n';
}
