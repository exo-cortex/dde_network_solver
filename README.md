# dde_network_solver 
## a programm for solving coupled delay differential equations written in C++

DDEs i.e. delay differential equations are differential equations in which a dynamical system's state's derivative also depends on the previous states. Many natural processes can be modelled as DDEs such as laser equations. This solver has network capabilities in order easily construct complex network topologies with multiple delays.

### Dependencies:
C++17, gcc, cmake, armadillo

### Compilation on Linux:
    mkdir build/
    cd build/
    cmake ..
    make .
or run:
    ./build.sh

### Conventions for commit messages:
prefix with a [tag] describing the category e.g. [feature], [bugfix], [etc].

### Features (already implemented (roughly))
* network class for easy contruction of networks

### Todo

* [dynamical systems] add {Stuart-Landau, Lang-Kobayashi, Microscopically-Derived-Rate-Equations, Lorenz-Attractor, Rössler-Attractor, ...} as dynamical systems. Use templates for base class.
* [analysis] implement timeseries analysis class with member functions for {min, max, uniqueMin, uniqueMax, globalAverage, ...}
* [parser] implement and improve upon old parser for full commandline-operation.
* [calculation] add poisson-disc sampling with adaptable disc-radius - implement adaptive sampling in order to sample only parameters in areas with interesting * results. 
* [rc] add reservoir-computing.
* [network] add methods for conversion between formats {list-of-edges, adjacency-matrices} and saving of networks into file, enable naming of edge-groups i.e. "edge-group [0] 'ring'".
* [logger/interface] add special output e.g. horizontal line, progress bar methods for contructing log output