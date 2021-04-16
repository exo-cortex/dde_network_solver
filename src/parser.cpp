#include "../include/parser.hpp"

using namespace std;

void parser::readCommandline(int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i){
        cout << argv[i] << '\t';
    }
    cout << '\n';


}

// void parser::findString(const string& flagName)
// {
    
// }