//
// Created by danie on 29/11/2022.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <array>

int main(int argc, char** argv){

    if(argc != 2 )
        return -1;

    //input file
    std::ifstream in_file;
    in_file.open(argv[1]);
    if(!in_file)
        return -1;

    //hyper-space dimension
    std::size_t dimensions;
    in_file >> dimensions;

    std::vector<float> function;
    std::vector<std::vector<float>> hyper_planes;
    float in_data;

    //function
    for (int i = 0; i < dimensions + 1; ++i){
        in_file >> in_data;
        function.push_back(in_data);
    }

    //hyper-planes
    while(!in_file.eof()){
        std::vector<float> hyper_plane;
        for(int i = 0; i < dimensions + 1; ++i){
            in_file >> in_data;
            hyper_plane.push_back(in_data);
        }
        hyper_planes.push_back(hyper_plane);
    }


    return 0;

}
