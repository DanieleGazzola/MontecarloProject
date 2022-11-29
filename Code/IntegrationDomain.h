//
// Created by danie on 29/11/2022.
//
#include <iostream>
#include <vector>

#ifndef MONTECARLOPROJECT_INTEGRATIONDOMAIN_H
#define MONTECARLOPROJECT_INTEGRATIONDOMAIN_H


class IntegrationDomain {
public:
    explicit IntegrationDomain(char* filename);
    float getDimension(int axis) { return dimensions.at(axis); }
    std::vector<float> getBaseVertex() { return baseVertex; }
    size_t getNDimensions() const{ return nDimensions; }

private:
    size_t nDimensions{};
    std::vector<float> dimensions;
    std::vector<float> baseVertex;

    void addBounds(std::pair<float, float>);

};


#endif //MONTECARLOPROJECT_INTEGRATIONDOMAIN_H
