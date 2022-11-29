//
// Created by danie on 29/11/2022.
//

#include <fstream>
#include "IntegrationDomain.h"

IntegrationDomain::IntegrationDomain(char *filename) {
    std::ifstream inFile;
    inFile.open(filename);
    inFile >> nDimensions;

    std::pair<float, float> bounds;

    for (int i = 0; i < nDimensions; ++i) {
        inFile >> bounds.first >> bounds.second;
        addBounds(bounds);
    }

    inFile.close();
}

void IntegrationDomain::addBounds(std::pair<float, float> bounds) {
    if (bounds.first == bounds.second)
        exit(-1);

    if (bounds.first > bounds.second)
        std::swap(bounds.first, bounds.second);

    dimensions.push_back(std::abs(bounds.second - bounds.first));
    baseVertex.push_back(bounds.first);

}
