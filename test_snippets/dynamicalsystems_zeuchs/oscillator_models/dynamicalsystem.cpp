#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <map>

using namespace std;

template <typename T>
class dynamicalSystem {
protected:
	typename std::vector<T> &history;
    typename std::vector<T>::iterator m_Delayed;
	double time;
public:
    dynamicalSystem(vector<T> &_history);
	virtual ~dynamicalSystem();
	void advanceIterator();
	virtual void update() = 0;
};

template <typename T>
dynamicalSystem<T>::dynamicalSystem(vector<T> &_history)
: history(_history), time(0)
{
	m_Delayed = history.end() - 1;
}

template <typename T>
dynamicalSystem<T>::~dynamicalSystem(){
}

template <typename T>
void dynamicalSystem<T>::advanceIterator() {
	if (++m_Delayed == history.end()) m_Delayed = history.begin();
}