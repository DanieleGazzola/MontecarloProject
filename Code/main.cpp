//
// Created by danie on 29/11/2022.
//

/*input file is formatted:
 * first line: n dimensions
 * other n lines: lower and upper bounds for each dimension
 *
 * */

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include "IntegrationDomain.h"

int main(int argc, char** argv){

    if(argc != 2 )
        return -1;

    std::ifstream in_file;
    in_file.open(argv[1]);
    if(!in_file)
        return -1;

    IntegrationDomain domain;

    size_t dimensions;
    in_file >> dimensions;

    std::pair<float, float> bounds;

    for (int i = 0; i < dimensions; ++i) {
        in_file >> bounds.first >> bounds.second;

        if(bounds.first == bounds.second)
            return -1;

        if(bounds.first < bounds.second)
            std::swap(bounds.first, bounds.second);

        domain.addBounds(bounds);
    }

    return 0;

}
