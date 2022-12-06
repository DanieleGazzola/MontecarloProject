//
// Created by danie on 01/12/2022.
//

#include "Geometry.hpp"
#include <fstream>
#include <cmath>
#include <random>
#include <string>

class HyperSphere : public Geometry{
public:
    explicit HyperSphere (char *filename){
        std::ifstream inFile;
        inFile.open(filename, std::ios_base::in);

        char *f = nullptr;
        inFile >> f;

        inFile >> nDimensions;
        centre.reserve(nDimensions);
        centre.resize(nDimensions);
        bounds.reserve(nDimensions);
        bounds.resize(nDimensions);
        inFile >> radius;

        for (int i = 0; i < nDimensions; ++i){
            inFile >> centre.at(i);
            bounds.at(i).first = centre.at(i) - radius;
            bounds.at(i).second = centre.at(i) + radius;
        }

        inFile.close();
        calculateModOmega();
    }

    std::vector<double> generatePoint(int rank, int i) override{
        std::vector<double> point;
        point.reserve(nDimensions);
        point.resize(nDimensions);

        bool checkPoint = true;
        int x = 0;
        double sum;

        do{
            sum = 0.;
            x++;
            const int seed = (rank + 1) * (i + 1) * (x + 1);
            std::mt19937 engine(seed);

            for (int j = 0; j < nDimensions; ++j){
                std::uniform_real_distribution<double> distribution(bounds.at(j).first, bounds.at(j).second);
                point.at(j) = distribution(engine);
                sum += (point.at(j) - centre.at(j)) * (point.at(j) - centre.at(j));
            }

            if(sum <= radius * radius)
                checkPoint = false;


        } while(checkPoint);

        return point;
    }

private:
    double radius{};
    std::vector<double> centre;
    std::vector<std::pair<double, double>> bounds;

    void calculateModOmega(){
        double hyperVolume = 1.;

        hyperVolume *= std::pow(radius, nDimensions);
        hyperVolume *= std::pow(M_PI, (nDimensions / 2));
        hyperVolume /= std::tgamma((nDimensions / 2) + 1);

        modOmega = hyperVolume;
    }

};
