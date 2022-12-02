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
    virtual std::vector<double> generatePoint(int rank, int i) = 0;
    size_t getNDimensions() const { return nDimensions; }
    double getModOmega() const { return modOmega; }

protected:
    size_t nDimensions{};
    double modOmega{};

};

#endif //MONTECARLOPROJECT_GEOMETRY_H
