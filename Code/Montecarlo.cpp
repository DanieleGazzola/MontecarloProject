//
// Created by danie on 02/12/2022.
//

#include <functional>
#include <vector>
#include "Geometry.hpp"
#include "mpi.h"
#include <omp.h>

class Montecarlo {
public:
    Montecarlo()= default;
    static void integrate(const std::function<float(std::vector<float>)>& f, long N, Geometry* domain){

        int rank, size;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        MPI_Bcast(&N, 1, MPI_LONG, 0, MPI_COMM_WORLD);

        const long mySamples = N / size + (rank < (N % size));


    };

    float getIntegral() const { return integral; }
    float getVariance() const { return variance; }

private:
    float integral;
    float variance;

};
