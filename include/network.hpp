#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include <complex>
#include <vector>
#include <iterator>
#include <random>

using namespace std;

struct edge{
	uint to;
	uint from;
	double delay, strength, phase;
	uint edgeGroup; // assign edge to a group (for later manipulation of edges by group)
	edge();
	edge(uint to, uint from, double delay, double strength, double phase, uint edgeGroup);
};

class network 
{
private:
	uint m_N; // number of nodes
	double m_delay, m_strength, m_phase; // default values
	uint m_currentEdgeGroup;
	vector<uint> m_edgeGroupList;
	vector<edge> m_allEdges; // has list of edges
	// has helper functions to check. (max delay from/to  node, number of connections from/to node etc)
	bool edgeIsNew(uint _toNode, uint _fromNode, double _delay);
	void countEdgeGroups();
public:
	void sumCouplingStrengths(); // make private?
	// constructors
	network(); // network created with 0 nodes
	network(uint N); // set / change number of nodes (can remove edges)
	network(uint N, double _delay, double _strength, double _phase); // set nodes and default values
	
	// methods to set / change number of nodes / set defaults
	void setNodes(uint N);
	void setDefaults( double _delay, double _strength, double _phase);
	void seedRandomSeed(uint _randomSeedWeights, int _randomSeedPhase, int _randomSeedDelay, int _randomSeedSmallworldRedirection);
	void setEdgeGroup(uint _newEdgeGroup);

	// methods to add edges
	void putEdge(uint _toNode, uint _fromNode);
	void putEdge(uint _toNode, uint _fromNode, double _delay);
	void putEdge(uint _toNode, uint _fromNode, double _delay, double _strength);
	void putEdge(uint _toNode, uint _fromNode, double _delay, double _strength, double _phase);
	
	// methods to add collections of edges
	void putRing();
	void putSmallRing(uint _nodeStart, uint _nodeEnd);
	void putChain();
	void putSmallChain(uint _nodeStart, uint _nodeEnd);
	void putDiagonal(int _offset);
	void putJumps(int _jumpDistance, int _jumpLength);
	// methods to remove edges
	void deleteEdge(uint to, uint from);
	void deleteEdge(uint to, uint from, double delay);
	
	// methods to convert into other formats
	void giveAdjacencyMatrix();
	void giveAdjacencyMatrixArmadillo(); // return an output that can be used to define an armadillo-matrix (in order to hard-code it (might benefit performance))
	
	// has methods to alter network
	void turnPhase(double _amount);
	void turnPhase(double _amount, uint _edgeGroup);
	void randomizeWeights(double _amount);
	void randomizeWeights(double _amount, uint _edgeGroup);
	void randomizePhase(double _amount);
	void randomizePhase(double _amount, uint _edgeGroup);
	void randomizeDelay(double _amount);
	void randomizeDelay(double _amount, uint _edgeGroup);

	void edgeChangeFromInterpolation(uint _to, uint _oldSender, uint _newSender, double _interpolationAmount);
	
	void smallWorldRedirect(double _redirectionLikelyhood);
	void smallWorldRedirect(double _redirectionLikelyhood, uint _edgeGroup);
	void smallWorldRedirectInterpolations(double _redirectionLikelyhood, double _interpolationAmount);
	void smallWorldRedirectInterpolations(double _redirectionLikelyhood, double _interpolationAmount, uint _edgeGroup);

	
	// methods that do not change the network
	void simplifyNetwork(); // if possible reduce number of edges and add edges
	void printNetwork();
	void printNetworkHelp();
};