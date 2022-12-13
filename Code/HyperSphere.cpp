//
// Created by danie on 01/12/2022.
//

#include "Geometry.hpp"
#include <fstream>
#include <cmath>
#include <random>
#include <string>
#include "mpi.h"

class HyperSphere : public Geometry{
public:
    explicit HyperSphere (char *filename){
        std::ifstream inFile;
        inFile.open(filename, std::ios_base::in);

        inFile >> function;
        //std::cout << function << std::endl;
        inFile >> nDimensions;
        //std::cout << nDimensions << std::endl;
        centre.reserve(nDimensions);
        centre.resize(nDimensions);
        inFile >> radius;
        if(radius == 0.)
            exit(-1);

        for (int i = 0; i < nDimensions; ++i)
            inFile >> centre.at(i);

        inFile.close();
        calculateModOmega();
    }

    std::vector<double> generatePoint(int i) override{
        std::vector<double> point;
        std::vector<double> angles;
        double pointRadius;

        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        point.reserve(nDimensions);
        point.resize(nDimensions);
        angles.reserve(nDimensions - 1);
        angles.resize(nDimensions - 1);

        const int seed = (rank + 1) * (i + 1);
        std::mt19937 engine(seed);
        std::uniform_real_distribution<double> distributionRadius(0., radius);
        pointRadius = distributionRadius(engine);

        for (int j = 0; j < nDimensions - 1; ++j) {
            if(j == nDimensions - 2){
                std::uniform_real_distribution<double> distribution(0., 2. * M_PI);
                angles.at(j) = distribution(engine);
            } else {
                std::uniform_real_distribution<double> distribution(0., M_PI);
                angles.at(j) = distribution(engine);
            }
        }

        for (int j = 0; j < nDimensions; ++j) {
            point.at(j) = pointRadius;
            for (int k = 0; k < j; ++k)
                point.at(j) *= std::sin(angles.at(k));
            if(j != nDimensions - 1)
                point.at(j) *= std::cos(angles.at(j));
        }

        for (int j = 0; j < nDimensions; ++j) {
            point.at(j) += centre.at(j);
        }

        return point;
    }

private:
    double radius{};
    std::vector<double> centre;

    void calculateModOmega(){
        double hyperVolume = 1.;

        hyperVolume *= std::pow(radius, nDimensions);
        hyperVolume *= std::pow(M_PI, (nDimensions / 2.));
        hyperVolume /= std::tgamma((nDimensions / 2.) + 1);

        modOmega = hyperVolume;
    }

};
