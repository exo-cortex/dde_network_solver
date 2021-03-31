#pragma once

#include <vector>
#include <fstream>

using namespace std;

struct uniqueExtremum {
    double value;
    unsigned int counts = 0;

};

template <state S>
class timeseries {
private:
    vector<S> currentSegment;

public:
};