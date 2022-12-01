//
// Created by danie on 29/11/2022.
//
#include <iostream>
#include <vector>

#ifndef MONTECARLOPROJECT_INTEGRATIONDOMAIN_H
#define MONTECARLOPROJECT_INTEGRATIONDOMAIN_H


class Geometry {
public:
    Geometry()= default;
    virtual std::vector<float> generatePoint();
    size_t getNDimensions() const { return nDimensions; }
    float getModOmega() const { return modOmega; }

protected:
    size_t nDimensions{};
    float modOmega{};

};



#endif //MONTECARLOPROJECT_INTEGRATIONDOMAIN_H
