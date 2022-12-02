//
// Created by danie on 29/11/2022.
//

/* Arguments:
 * domain type: 0 rectangle
 *              1 sphere
 * n samples
 * file name
 *
 *
 * input file is formatted:
 * first line: domain dimension
 * other n lines: bounds for each dimension
 *
 * or
 *
 * first line: domain dimension
 * second line: sphere's centre in n dimensions
 * */

#include "Montecarlo.cpp"
#include "HyperRectangle.cpp"
#include "HyperSphere.cpp"
#include "mpi.h"
#include <cmath>

int main(int argc, char** argv){

    if(argc != 4)
        return -1;

    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    auto domainType = strtol(argv[1], nullptr, 10);
    auto N = strtol(argv[2], nullptr, 10);
    Montecarlo montecarlo{};

    Geometry* domain;

    if(domainType == 0){
        domain = new HyperRectangle(argv[3]);
    } else if(domainType == 1){
        domain = new HyperSphere(argv[3]);
    } else {
        return -1;
    }

    montecarlo.integrate([](std::vector<double> x) { return std::sqrt(1 - x.at(0) * x.at(0)); }, N, domain);

    if(rank == 0){
        std::cout << "Integral: " << montecarlo.getIntegral() << std::endl
                  << "Estimated error: " << std::sqrt(montecarlo.getVariance()) << std::endl;
        std::cout << "Domain dimension: " << domain->getNDimensions() << std::endl
                  << "Domain volume: " << domain->getModOmega() << std::endl;
    }

    MPI_Finalize();

    return 0;
}
