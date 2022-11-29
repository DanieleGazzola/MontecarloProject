//
// Created by danie on 29/11/2022.
//
#include <iostream>
#include <vector>

#ifndef MONTECARLOPROJECT_INTEGRATIONDOMAIN_H
#define MONTECARLOPROJECT_INTEGRATIONDOMAIN_H


class IntegrationDomain {
public:
    void addBounds(std::pair<float, float> bounds);
    void calculateVertices();
    float getDimension(int axis);
    std::vector<float> getBaseVertex();

private:
    std::vector<float> dimensions;
    std::vector<float> baseVertex;

};


#endif //MONTECARLOPROJECT_INTEGRATIONDOMAIN_H
