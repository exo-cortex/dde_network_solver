#include "../include/parse_functions.hpp"

using namespace std;

bool is_number(const string& s){
	try{
		stod(s);
	}
	catch(...){
		return false;
	}
	return true;
}

void readParameters(map<const string, double> &parameterMap, int _argc, char* _argv[]){
	cout << "you gave me " << _argc << " arguments. parsing...\n";
	if (_argc == 1) return;
	for (int clIndex = 1; clIndex < _argc - 1; clIndex++) {
		for (pair<const string, double> &key : parameterMap) {
			if (string(_argv[clIndex]) == ('-' + key.first) && _argc > clIndex && is_number(_argv[clIndex+1])) {
				key.second = stod(_argv[clIndex+1]);
				cout << "set [-\033[1;31m" << key.first << "\033[0;39m] to " << key.second << ".\n" ;
				continue;
			}
		}
	}
}