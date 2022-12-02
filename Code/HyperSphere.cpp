//
// Created by danie on 01/12/2022.
//

#include "Geometry.hpp"
#include <fstream>


class HyperSphere : public Geometry{
public:
    explicit HyperSphere (char *filename){
        std::ifstream inFile;
        inFile.open(filename, std::ios_base::in);

        inFile >> nDimensions;
        centre.reserve(nDimensions);
        centre.resize(nDimensions);
        inFile >> radius;

        for (int i = 0; i < nDimensions; ++i)
            inFile >> centre.at(i);

        inFile.close();
        calculateModOmega();
    }

private:
    float radius{};
    std::vector<float> centre;

    void calculateModOmega(){
        //da fare
    }

};