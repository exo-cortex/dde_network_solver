#include "oscillator_models/dynamicalsystem.cpp"
#include "oscillator_models/oscillator_lorenz.cpp"
#include "oscillator_models/oscillator_langkobayashi.cpp"
#include "oscillator_models/oscillator_stuartlandau.cpp"
#include "oscillator_models/oscillator_mackeyglass.cpp"
#include "oscillator_models/oscillator_roessler.cpp"
#include "parse_with_map.cpp"

using namespace std;

// parameters that you can change in  the console (preface with '-')
map<const string, double> myParameters {
	//general parameters
	{"dt", 0.001}, {"runsilent", 0}, {"runtime", 100}, {"delay", 12.0}, {"fill_history", 0.0},

	//lorenz system
	{"sigma", 10.0 }, {"beta", 8.0/3.0}, {"rho", 28.0}, {"kappa", 0.0},

	//stuart-landau system
	{"lambda", -0.05 }, {"omega", 1.0}, {"gammaRe", -0.1}, {"gammaIm", 0.0},
	
	//mackey-glass system
	{"beta0", 0.2}, {"theta", 1.0}, {"n", 10}, {"gamma", 0.1},

	//roessler attractor
	{"a", 0.1}, {"b", 0.1}, {"c", 14.0},

	//lang-kobayashi
	{"alpha", 0.25}, {"P", 1.0}, {"T_LK", 1000.0}, {"kappa", 0.1}, {"phi", 0.0}
	};


int main(int argc, char* argv[]){

	readParameters(myParameters, argc, argv); // search argv[] for keys of 'myParameters'

	typedef double keep; // depending on the oscillator model, various types are kept in the 'history' used for delay-coupling.
	uint historySize = (uint)(myParameters["delay"]/myParameters["dt"]);
	vector<keep> historyVector(historySize, myParameters["fill_history"]);
	mackeyGlassSystem mySystem(historyVector, myParameters);

	ofstream file("output1.txt");

	for (uint i = 0; i < (uint)(myParameters["runsilent"]/myParameters["dt"]); i++) {
		for (uint j = 0; j < 100; j++ ) {
			mySystem.update();
		}
	}



	for (uint i = 0; i < (uint)(myParameters["runtime"]/myParameters["dt"]); i++) {
		for (uint j = 0; j < 100; j++ ) {
			mySystem.update();
		}
		mySystem.writeParametricState(file);
		// mySystem.writeAmplitude(file);
	}
}