//
// Created by danie on 29/11/2022.
//

#include "IntegrationDomain.h"

void IntegrationDomain::addBounds(std::pair<float, float> bounds) {
    float size = bounds.first - bounds.second;
    dimensions.push_back(size);
}
