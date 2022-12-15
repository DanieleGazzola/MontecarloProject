//
// Created by danie on 29/11/2022.
//

#include <cmath>
#include <chrono>
#include "Montecarlo.cpp"
#include "HyperRectangle.cpp"
#include "HyperSphere.cpp"
#include "mpi.h"
#include "muParser.h"

int main(int argc, char** argv){

    if(argc != 5){
        std::cout << "Wrong number of command line arguments" << std::endl;
        return -1;
    }

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const auto domainType = std::strtol(argv[1], nullptr, 10);
    const auto N = std::strtol(argv[2], nullptr, 10);

    Montecarlo montecarlo{};
    std::shared_ptr<Geometry> domain;

    switch(domainType) {
        case 0: {
            domain = std::make_shared<HyperRectangle>(argv[3]);
            break;
        }
        case 1: {
            domain = std::make_shared<HyperSphere>(argv[3]);
            break;
        }
        default:
            return -1;
    }

    auto start = std::chrono::system_clock::now();
    montecarlo.integrate(domain, N, std::stoi(argv[4]));
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;

    if(rank == 0){
        std::cout << "Integral: " << montecarlo.getIntegral() << std::endl
                  << "Estimated error: " << std::sqrt(montecarlo.getVariance()) << std::endl
                  << "Target error: " << montecarlo.getIntegral() / std::sqrt(N) << std::endl;
        std::cout << "Domain dimension: " << domain->getNDimensions() << std::endl
                  << "Domain volume: " << domain->getModOmega() << std::endl;
        std::cout << "Elapsed time: " << elapsed_seconds.count() << " s" << std::endl;
    }

    MPI_Finalize();

    return 0;
}
