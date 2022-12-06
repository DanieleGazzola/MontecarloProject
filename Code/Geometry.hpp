//
// Created by danie on 29/11/2022.
//
#include <iostream>
#include <vector>
#include <string>

#ifndef MONTECARLOPROJECT_GEOMETRY_H
#define MONTECARLOPROJECT_GEOMETRY_H


class Geometry {
    public:
        Geometry()= default;
        virtual std::vector<double> generatePoint(int rank, int i) = 0;
        const int getNDimensions() const { return nDimensions; }
        double getModOmega() const { return modOmega; }
        const char* getFunction() const { return function; }

    protected:
        char function[50];
        int nDimensions{};
        double modOmega{};
};

#endif //MONTECARLOPROJECT_GEOMETRY_H
