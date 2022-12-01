//
// Created by danie on 01/12/2022.
//

#include "Geometry.hpp"
#include <fstream>


class HyperRectangle : public Geometry{
public:
    explicit HyperRectangle (char *filename){
        std::ifstream inFile;
        inFile.open(filename, std::ios_base::in);

        inFile >> nDimensions;
        bounds.reserve(nDimensions);
        bounds.resize(nDimensions);

        for (int i = 0; i < nDimensions; ++i)
            inFile >> bounds.at(i).first >> bounds.at(i).second;

        inFile.close();
        calculateModOmega();
    }

private:
    std::vector<std::pair<float, float>> bounds;

    void calculateModOmega(){
        float hyperVolume = 1.;
        for (auto bound : bounds)
            hyperVolume *= std::abs(bound.first - bound.second);

        modOmega = hyperVolume;
    }

};
