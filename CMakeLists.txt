cmake_minimum_required(VERSION 3.23)
project(MontecarloProject)

set(CMAKE_CXX_STANDARD 14)

find_package(MPI REQUIRED)

set(PROJECT_HEADERS
        Code/Geometry.hpp
        )

set(PROJECT_SOURCES
        Code/main.cpp
        Code/HyperRectangle.cpp
        Code/HyperSphere.cpp
        Code/Montecarlo.cpp
        )

add_executable(MontecarloProject
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS})

target_link_libraries(MontecarloProject PUBLIC MPI::MPI_CXX)
