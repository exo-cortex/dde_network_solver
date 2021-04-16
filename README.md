# dde_network_solver 
## a programm for solving coupled delay differential equations written in C++

this solver has network capabilities in order easily construct complex network topologies with multiple delays.

### Needed packages: 
C++17, gcc, cmake, armadillo

### Compilation on Linux:
    mkdir build/
    cd build/
    cmake ..
    make .
or run:
    ./build.sh

### conventions for commit messages:
prefix with a [tag] describing the category e.g. [feature], [bugfix], [etc]. 

### FEATURES (already implemented (roughly))
* network class for easy contruction of networks

### TODO

* [dynamical systems] add {Stuart-Landau, Lang-Kobayashi, ...} as dynamical systems
* [analysis] implement timeseries analysis class with member functions for {min, max, uniqueMin, uniqueMax, globalAverage, simplifyAndSave, ...}
* [parser] implement and improve upon old parser for full commandline-operation
* [calculation] add poisson-disc sampling with adaptable disc-radius - implement adaptive sampling in order to sample only parameters in areas with interesting * results. 
* [rc] add reservoir-computing.
* [network] add methods for conversion between formats {list-of-edges, adjacency-matrices} and saving of networks into file.