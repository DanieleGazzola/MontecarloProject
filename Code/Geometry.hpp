//
// Created by danie on 29/11/2022.
//
#include <iostream>
#include <vector>

#ifndef MONTECARLOPROJECT_GEOMETRY_H
#define MONTECARLOPROJECT_GEOMETRY_H


class Geometry {
public:
    Geometry()= default;
    virtual std::vector<float> generatePoint(){ return {}; };
    size_t getNDimensions() const { return nDimensions; }
    float getModOmega() const { return modOmega; }

protected:
    size_t nDimensions{};
    float modOmega{};

};

#endif //MONTECARLOPROJECT_GEOMETRY_H
