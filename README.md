# dde_network_solver 
## a programm for solving coupled delay differential equations written in C++

this solver has network capabilities in order easily construct complex network topologies with multiple delays.

### Needed packages: 
C++, gcc, cmake, armadillo

### Compilation on Linux:
    mkdir build/
    cd build/
    cmake ..
    make .
or run:
    ./build.sh

### conventions for commit messages:
prefix with a [tag] describing the category e.g. [feature], [bugfix], [dod]. 

### TODO

* [feature] add {Stuart-Landau, Lang-Kobayashi, ...} as dynamical systems
* [feature] implement timeseries analysis class with member functions for {min, max, uniqueMin, uniqueMax, globalAverage, simplifyAndSave, ...}
* [feature] implement and improve upon old parser for full commandline-operation
* ...
* [feature] add poisson-disc sampling with adaptable disc-radius - implement adaptive sampling in order to sample only parameters in areas with interesting * results. 
* [feature] add reservoir-computing.