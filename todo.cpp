//this isn't a real c++-file. 
//It is simply a todo-file with c++-formatting.

// #include <iostream>
// #include <string>
// #include <fstream>
// #include <vector>
// #include <map>
// #include <variant>
// #include <armadillo>
// todo

using namespace std;

timeseries:
	fine timeseries of state for integration and delay
	coarse timeseries for analysis and saving
];

class calculation
{
	// has parameter range to scan
	vector<vector<double>> m_ranges;
	vector<string> keys;
	double m_maxRadius, m_minRadius;
	vector<vector<double>> samples;
	void samplePoisson(double _radius);
	void sampleGrid(double _radius);
	void parameterFromSample(uint index); // turns the sample into a set of parameters
}

class parameter
{

}

class parseObject
{
	string flagName;
	variant<bool, uint, int, double, complex<double>> flagValue;
}

void parseSomething (uint index, int argc, char* argv[], map<string, variant<bool, uint, int, double, complex<double>) _map)
{
	for (auto a : _map.keys())
}


class capacity
{
private:
	// results...
	

	arma::mat* statematrix;
	arma::mat m_alteredStatematrix;

	bool doSingleNodes, doOmittedNodes, doNARMA;
	
public:

	void setupTasks();
}