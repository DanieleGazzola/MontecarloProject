cmake_minimum_required(VERSION 3.23)
project(MontecarloProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-fopenmp")

find_package(MPI REQUIRED)
find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()

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
