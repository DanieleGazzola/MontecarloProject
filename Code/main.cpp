//
// Created by danie on 29/11/2022.
//

/* input file is formatted:
 * first line: domain dimension
 * other n lines: bounds for each dimension
 * */

#include "Geometry.hpp"
#include "HyperRectangle.cpp"
#include "mpi.h"

int main(int argc, char** argv){

    if(argc != 2 ) return -1;

    MPI_Init(NULL, NULL);

    HyperRectangle domain(argv[1]);

    std::cout << domain.getNDimensions();

    return 0;
}
