#pragma once

#include <iostream>
#include <string>
#include <map>

using namespace std;

bool is_number(const string& s);

void readParameters(map<const string, double> &parameterMap, int _argc, char* _argv[]);