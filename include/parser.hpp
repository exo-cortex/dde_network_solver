#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <map>

using namespace std;

class parser 
{

// private:
    uint m_commandlineLength;
    vector<string> m_commandlineStrings;
public:
    
    void readCommandline(int argc, char *argv[]);
    
    // void readConstants();
    // void readIntegrationParameters();
    // void readNodeParameters();
    // void readNetworkParameters();
    // void readAnalysisParameters();
    // smaller methods 
    // void findString(const string& flagName);
};