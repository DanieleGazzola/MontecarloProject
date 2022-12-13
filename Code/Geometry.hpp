//
// Created by danie on 29/11/2022.
//
#include <iostream>
#include <vector>
#include <string>
#include <random>

#ifndef MONTECARLOPROJECT_GEOMETRY_H
#define MONTECARLOPROJECT_GEOMETRY_H


class Geometry {
    public:
        Geometry()= default;

        virtual std::vector<double> generatePoint() = 0;

        int getNDimensions() const { return nDimensions; }
        double getModOmega() const { return modOmega; }
        const std::string getFunction() const { return function; }

    protected:
        std::string function{};
        int nDimensions{};
        double modOmega{};
        std::mt19937 engine;
};

#endif //MONTECARLOPROJECT_GEOMETRY_H
