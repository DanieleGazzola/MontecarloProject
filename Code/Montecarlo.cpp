//
// Created by danie on 02/12/2022.
//

#include <functional>
#include <vector>
#include "Geometry.hpp"

class Montecarlo {
public:
    Montecarlo()= default;
    void integrate(const std::function<float(std::vector<float>)>& f, long N, Geometry* domain){

    };

    float getIntegral() const { return integral; }
    float getVariance() const { return variance; }

private:
    float integral;
    float variance;

};
