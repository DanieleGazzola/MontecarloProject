//
// Created by danie on 29/11/2022.
//

#include "Montecarlo.cpp"
#include "HyperRectangle.cpp"
#include "HyperSphere.cpp"
#include "mpi.h"
#include <cmath>
#include <chrono>
#include "muParser.h"

int main(int argc, char** argv){

    if(argc != 4)
        return -1;

    auto domainType = strtol(argv[1], nullptr, 10);
    auto N = strtol(argv[2], nullptr, 10);
    Montecarlo montecarlo{};

    Geometry* domain;

    switch(domainType){
        case 0:
            domain = new HyperRectangle(argv[3]);
            break;
        case 1:
            domain = new HyperSphere(argv[3]);
            break;
        default:
            return -1;
    }

    auto start = std::chrono::system_clock::now();

    montecarlo.integrate(argv[3], N, domain);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << "Integral: " << montecarlo.getIntegral() << std::endl
              << "Estimated error: " << std::sqrt(montecarlo.getVariance()) << std::endl;
    std::cout << "Domain dimension: " << domain->getNDimensions() << std::endl
              << "Domain volume: " << domain->getModOmega() << std::endl;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << " s" << std::endl;

    return 0;
}
