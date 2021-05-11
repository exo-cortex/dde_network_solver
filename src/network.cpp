#include "../include/logger.hpp"
#include "../include/constants.hpp"
#include "../include/network.hpp"

using namespace std;

bool ADD_WEIGHTS = false;

std::vector<std::mt19937> NETWORK_RANDOM_NUMBER_GENERATOR(4);
std::uniform_real_distribution<double> UNIFORM_SYMMETRIC(-1,1);
std::uniform_real_distribution<double> UNIFORM(0,1);

// edge
edge::edge(){};

edge::edge(uint to, uint from, double delay, double strength, double phase, uint edgeGroup)
	: to(to), from(from), delay(delay), strength(strength), phase(phase), edgeGroup(edgeGroup){};


// network
network::network(string _edgeGroup)
	: m_N(0), m_currentEdgeGroup(0) {
		m_edgeGroups.emplace_back(_edgeGroup);
	};

network::network(uint N, string _edgeGroup)
	: m_N(N), m_currentEdgeGroup(0) {
		m_edgeGroups.emplace_back(_edgeGroup);
	};

network::network(uint N, double _delay, double _strength, double _phase, string _edgeGroupName)
	: m_N(N), m_delay(_delay), m_strength(_strength), m_phase(_phase), m_currentEdgeGroup(0) {
		m_edgeGroups.emplace_back(_edgeGroupName);
	};

void network::setNodes(uint _N){
	if (_N >= m_N) m_N = _N;
	else {
		vector<edge>::iterator edgeIt = begin(m_allEdges);
		while (edgeIt != m_allEdges.end()){
			if ((*edgeIt).to >= _N || (*edgeIt).from >= _N) m_allEdges.erase(edgeIt);
			else ++edgeIt;
		}
	}
}

// helper methods
void network::setDefaults(double _delay, double _strength, double _phase, string _currentEdgeGroupName){
	m_delay = _delay;
	m_strength = _strength;
	m_phase = _phase;
	// *(m_edgeGroups.end() - 1) = _currentEdgeGroupName;
}

void network::seedRandomSeed(uint _randomSeedWeights, int _randomSeedPhase = -1, int _randomSeedDelay = -1, int _randomSeedSmallworldRedirection = -1){
	NETWORK_RANDOM_NUMBER_GENERATOR[0].seed(_randomSeedWeights);
	if (_randomSeedPhase == -1) NETWORK_RANDOM_NUMBER_GENERATOR[1].seed(_randomSeedWeights);
	if (_randomSeedDelay == -1) NETWORK_RANDOM_NUMBER_GENERATOR[2].seed(_randomSeedWeights);
	if (_randomSeedSmallworldRedirection == -1) NETWORK_RANDOM_NUMBER_GENERATOR[3].seed(_randomSeedWeights);
}

void network::nextEdgeGroup(string _edgeGroupName) {
	m_edgeGroups.emplace_back(_edgeGroupName);
	m_currentEdgeGroup += 1;
}

void network::selectExistingEdgeGroup(uint _edgeGroupIndex) {
	if (_edgeGroupIndex < m_edgeGroups.size()) m_currentEdgeGroup = _edgeGroupIndex;
	return;
}

bool network::edgeIsNew(uint _toNode, uint _fromNode, double _delay){
	for (edge &e : m_allEdges){
		if (e.to == _toNode && e.from == _fromNode && e.delay == _delay) return false;
	}
	return true;
}

void network::sumCouplingStrengths(){
	vector<edge> tempEdges;

	vector<edge>::iterator edgeIt = begin(m_allEdges);
	vector<edge>::iterator edgeItCompare = begin(m_allEdges)+1;

	while (edgeIt != m_allEdges.end()){
		complex<double> combinedWeight = (*edgeIt).strength * exp(1i * (*edgeIt).phase * 2.0 * M_PI);
		bool wasModified = false;
		cout << combinedWeight << '\n';
		while (edgeItCompare != m_allEdges.end()){
			if ((*edgeIt).to == (*edgeItCompare).to && (*edgeIt).from == (*edgeItCompare).from && (*edgeIt).delay == (*edgeItCompare).delay){
				combinedWeight += (*edgeItCompare).strength * exp(1i * (*edgeItCompare).phase * 2.0 * M_PI);
				cout << "erasing edge: " << (*edgeItCompare).to << " <-- " << (*edgeItCompare).from << "\n";
				m_allEdges.erase(edgeItCompare);
				wasModified = true;
			}
			++edgeItCompare;
		}
		if (wasModified){
			(*edgeIt).strength = abs(combinedWeight);
			(*edgeIt).phase = fmod(arg(combinedWeight) / (2.0 * M_PI), 1);
		}
		++edgeIt;
	}

}


// single edges
void network::putEdge(uint _toNode, uint _fromNode){
	putEdge(_toNode, _fromNode, m_delay, m_strength, m_phase);
}
void network::putEdge(uint _toNode, uint _fromNode, double _delay){
	putEdge(_toNode, _fromNode, _delay, m_strength, m_phase);
}
void network::putEdge(uint _toNode, uint _fromNode, double _delay, double _strength){
	putEdge(_toNode, _fromNode, _delay, _strength, m_phase);
}

void network::putEdge(uint _toNode, uint _fromNode, double _delay, double _strength, double _phase){
	if (_toNode >= m_N || _fromNode >= m_N) return;
	if (edgeIsNew(_toNode, _fromNode, _delay)) m_allEdges.push_back(edge(_toNode, _fromNode, _delay, _strength, _phase, m_currentEdgeGroup));
	else { // if a similar edge already exists
		for (edge &e : m_allEdges){
			if (e.to == _toNode && e.from == _fromNode && e.delay == _delay){
				if (ADD_WEIGHTS){
					complex<long double> weight = e.strength * exp(1i * 2.0 * M_PI * e.phase) + _strength * exp(1i * 2.0 * M_PI * _phase);
					e.strength = abs(weight);
					e.phase = fmod(arg(weight) / (2.0 * M_PI), 1);
				}
			}
		}
	}
}

void network::putRing(){
	for (uint Ni = 0; Ni < m_N; ++Ni){
		putEdge(Ni, (Ni - 1 + m_N) % m_N);
	}
}

void network::putSmallRing(uint _nodeStart, uint _nodeEnd){
	putEdge(_nodeStart, _nodeEnd);
	for (uint Ni = _nodeStart + 1; Ni <= _nodeEnd; ++Ni){
		putEdge(Ni, Ni - 1);
	}
}

void network::putChain(){
	for (uint Ni = 1; Ni <= m_N; ++Ni){
		putEdge(Ni, Ni - 1);
	}
}

void network::putSmallChain(uint _nodeStart, uint _nodeEnd){
	for (uint Ni = _nodeStart + 1; Ni <= _nodeEnd; ++Ni){
		putEdge(Ni, Ni - 1);
	}
}

void network::putDiagonal(int _offset){
	for (uint Ni = 0; Ni < m_N; ++Ni){
		putEdge(Ni, (Ni + _offset + m_N) % m_N);
	}
}

void network::putJumps(int _jumpDistance, int _jumpLength){
	for (uint Ni = 0; Ni < m_N; Ni+= _jumpDistance){
		putEdge(Ni, (Ni - _jumpLength) % m_N);
	}
}

void network::deleteEdge(uint _toNode, uint _fromNode){
	vector<edge>::iterator edgeIt = begin(m_allEdges);
	while (edgeIt != m_allEdges.end()){
		if ((*edgeIt).to == _toNode && (*edgeIt).from == _fromNode) m_allEdges.erase(edgeIt);
		else ++edgeIt;
	}
}

void network::deleteEdge(uint _toNode, uint _fromNode, double _delay){
	vector<edge>::iterator edgeIt = begin(m_allEdges);
	while (edgeIt != m_allEdges.end()){
		if ((*edgeIt).to == _toNode && (*edgeIt).from == _fromNode && (*edgeIt).delay == _delay) m_allEdges.erase(edgeIt);
		else ++edgeIt;
	}
}

void network::turnPhase(double _amount){
	for (edge &e : m_allEdges)
		e.phase += _amount;
}

void network::turnPhase(double _amount, uint _edgeGroup){
	for (edge &e : m_allEdges){
		if (e.edgeGroup == _edgeGroup) e.phase += _amount;
	}
}

void network::randomizeWeights(double _amount){
	for (edge &e : m_allEdges){
		e.strength *= (1 + _amount * UNIFORM_SYMMETRIC(NETWORK_RANDOM_NUMBER_GENERATOR[0]));
	}
}

void network::randomizeWeights(double _amount, uint _edgeGroup){
	for (edge &e : m_allEdges){
		if (e.edgeGroup == _edgeGroup) e.strength *= (1 + _amount * UNIFORM_SYMMETRIC(NETWORK_RANDOM_NUMBER_GENERATOR[0]));
	}
}

void network::randomizePhase(double _amount){
	for (edge &e : m_allEdges){
		e.phase += _amount * UNIFORM_SYMMETRIC(NETWORK_RANDOM_NUMBER_GENERATOR[1]);
	}
}

void network::randomizePhase(double _amount, uint _edgeGroup){
	for (edge &e : m_allEdges){
		if (e.edgeGroup == _edgeGroup) e.phase += _amount * UNIFORM_SYMMETRIC(NETWORK_RANDOM_NUMBER_GENERATOR[1]);
	}
}

void network::randomizeDelay(double _amount){
	for (edge &e : m_allEdges){
		e.delay *= 1 + _amount * UNIFORM_SYMMETRIC(NETWORK_RANDOM_NUMBER_GENERATOR[2]);
	}
}

void network::randomizeDelay(double _amount, uint _edgeGroup){
	for (edge &e : m_allEdges){	
		if (e.edgeGroup == _edgeGroup) e.delay *= 1 + _amount * UNIFORM_SYMMETRIC(NETWORK_RANDOM_NUMBER_GENERATOR[2]);
	}
}

void network::smallWorldRedirect(double _redirectionLikelyhood){
	for (edge &e : m_allEdges){
		double randomValue = UNIFORM_SYMMETRIC(NETWORK_RANDOM_NUMBER_GENERATOR[3]);
		if (randomValue < _redirectionLikelyhood){
			uint newSender = (uint)(m_N * (0.5 + 0.5 * UNIFORM_SYMMETRIC(NETWORK_RANDOM_NUMBER_GENERATOR[3])));
			e.from = newSender;
		}
	}
}

void network::smallWorldRedirect(double _redirectionLikelyhood, uint _edgeGroup){
	for (edge &e : m_allEdges){
		if (e.edgeGroup == _edgeGroup){
			double randomValue = UNIFORM_SYMMETRIC(NETWORK_RANDOM_NUMBER_GENERATOR[3]);
			if (randomValue < _redirectionLikelyhood){
				uint newSender = (uint)(m_N * (0.5 + 0.5 * UNIFORM_SYMMETRIC(NETWORK_RANDOM_NUMBER_GENERATOR[3])));
				e.from = newSender;
			}
		}
	}
}

void network::edgeChangeFromInterpolation(uint _to, uint _oldSender, uint _newSender, double _interpolationAmount){
	edge temp;
	for (edge& e : m_allEdges){
		if (e.to == _to && e.from == _oldSender){
			temp = edge(e.to, _newSender, e.delay, e.strength * _interpolationAmount, e.phase, m_currentEdgeGroup);
			e.strength *= (1 - _interpolationAmount);
		}
	}
	m_allEdges.push_back(temp);
}

void network::smallWorldRedirectInterpolations(double _redirectionLikelyhood, double _interpolationAmount){
	vector<edge> tempEdges;
	for (edge &e : m_allEdges){
		double randomValue = UNIFORM(NETWORK_RANDOM_NUMBER_GENERATOR[3]);
		if (randomValue < _redirectionLikelyhood){
			uint newSender = (uint)(m_N * UNIFORM(NETWORK_RANDOM_NUMBER_GENERATOR[3]));
			double tempStrength = e.strength;
			e.strength = e.strength * (1 - _interpolationAmount);
			tempEdges.push_back(edge(e.to, newSender, e.delay, tempStrength * _interpolationAmount, e.phase, m_currentEdgeGroup));
		}
	}
	for (edge& te : tempEdges){
		m_allEdges.push_back(te);
	}
}



// logging
void network::printNetwork()
{
	cout << "showing contents of network:\n";
	cout << m_N << " nodes with " << m_allEdges.size() << " edges in " << m_edgeGroups.size() << " edge groups [ ";
	for (uint egN = 0; egN < m_edgeGroups.size(); ++egN){
		cout << egN << ' ';
	}
	cout << "]\n";

	for (uint egN = 0; egN < m_edgeGroups.size(); ++egN)
	{
		LOG(INFO, CYAN) << LOG().printline();
		LOG(INFO) << " edge group [" << LOG().color(YELLOW, BOLD) << egN << LOG().color(NONE, DEFAULT) << "] \"" << m_edgeGroups[egN] << "\"";
		for (uint Ni = 0; Ni < m_N; ++Ni)
		{
			// cout << "node " 	<< setw(2) << Ni << "\n";
			for (const edge &e : m_allEdges)
			{
				if (e.edgeGroup == egN && e.to == Ni)
				{
					LOG(INFO) << "\t" << setw(2) << setfill(' ') << e.to << " <-- " << e.from << setprecision(4) << setw(4) << setfill('0') << "\tdelay = " << e.delay << "\tkappa = " << e.strength << "\tphi/2pi = " << e.phase << "\t";
				}
			}
		}
	}
	LOG(INFO, CYAN) << LOG().printline();
}

void network::printNetworkHelp()
{
	cout << "network class v0.1. a class that creates delay-coupled networks based on edges.\nedges consist of: [reveiver] <-- [sender], delay tau, strength kappa and phase phi.\n";
}
