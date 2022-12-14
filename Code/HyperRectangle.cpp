//
// Created by danie on 01/12/2022.
//

#include "Geometry.hpp"
#include <fstream>
#include <random>
#include <string>
#include "mpi.h"


class HyperRectangle : public Geometry{
    public:
        explicit HyperRectangle (std::string filename){
            std::ifstream inFile;
            inFile.open(filename, std::ios_base::in);

            inFile >> function;
            //std::cout << function << std::endl;
            inFile >> nDimensions;
            //std::cout << nDimensions << std::endl;
            bounds.reserve(nDimensions);
            bounds.resize(nDimensions);

            for (int i = 0; i < nDimensions; ++i) {
                inFile >> bounds.at(i).first >> bounds.at(i).second;
                if(bounds.at(i).first == bounds.at(i).second)
                    exit(-1);
                if(bounds.at(i).first > bounds.at(i).second)
                    std::swap(bounds.at(i).first, bounds.at(i).second);
            }

            int rank;
            MPI_Comm_rank(MPI_COMM_WORLD, &rank);
            engine.seed(rank);

            inFile.close();

            if(rank == 0)
                calculateModOmega();
        }

        std::vector<double> generatePoint() override{
            std::vector<double> point;
            point.reserve(nDimensions);
            point.resize(nDimensions);

            for (int j = 0; j < nDimensions; ++j){
                std::uniform_real_distribution<double> distribution(bounds.at(j).first, bounds.at(j).second);
                point.at(j) = distribution(engine);
            }

            return point;
        }

    private:
        std::vector<std::pair<double, double>> bounds;

        void calculateModOmega(){
            double hyperVolume = 1.;
            for (auto bound : bounds)
                hyperVolume *= std::abs(bound.first - bound.second);

            modOmega = hyperVolume;
        }
};
