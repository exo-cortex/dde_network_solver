#include <iostream>
#include <armadillo>

// see https://stackoverflow.com/questions/67195147/directly-accessing-entries-of-armadillo-matrix-by-memory-pointer-memptr-does-n

struct someStruct {
	const double *currentStateInMatrix;
	void printvalue() {std::cout << "*currentState (pointer to first enty of matrix) = " << *currentStateInMatrix << std::endl;}
};

int main(int argc, char* argv[]){

	uint M_size = 4;

	arma::Mat<double> M(M_size, M_size, arma::fill::randu);

	double* pointerIntoMatrix = M.memptr();
	std::cout << "pointer [ " << pointerIntoMatrix << " ] has value: " << *pointerIntoMatrix << std::endl;

	someStruct myStruct;
	myStruct.currentStateInMatrix = pointerIntoMatrix;

	std::cout << "original matrix M: \n" << M;
	myStruct.printvalue();
	std::cout << "\n+++changing contents of matrix M+++\n\n";

	M = M * M;

	std::cout << "M * M: \n" << M;
	myStruct.printvalue();
}