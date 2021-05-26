#include "../include/logger.hpp"
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
	LOG(DEBUG) << "you gave me " << _argc << " arguments. parsing...";
	if (_argc == 1) return;
	for (int clIndex = 1; clIndex < _argc - 1; clIndex++) {
		for (pair<const string, double> &key : parameterMap) {
			if (string(_argv[clIndex]) == '-' + key.first && _argc > clIndex && is_number(_argv[clIndex+1])) {
				key.second = stod(_argv[clIndex+1]);
				LOG(DEBUG) <<  "set [" << LOG().color(BLUE, BOLD) << "-" << key.first << LOG().color(NONE) << "] = " << key.second << ".";
				continue;
			}
		}
	}
}