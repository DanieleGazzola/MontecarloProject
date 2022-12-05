//
// Created by danie on 02/12/2022.
//

#include <functional>
#include <vector>
#include <cmath>
#include "Geometry.hpp"
#include "mpi.h"

class Montecarlo {
public:
    Montecarlo() = default;
    void integrate(const std::function<double(std::vector<double>)>& f, long N, Geometry* domain){

        int rank, size;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        MPI_Bcast(&N, 1, MPI_LONG, 0, MPI_COMM_WORLD);

        MPI_Barrier(MPI_COMM_WORLD);

        const long mySamples = N / size + (rank < (N % size));
        double mySum = 0.;
        double mySumSquared = 0.;

        #pragma omp parallel for default(none) shared(mySamples, domain, rank, f) reduction(+ : mySum , mySumSquared)
        for (int i = 0; i < mySamples; ++i) {
            auto sample = domain->generatePoint(rank, i);
            auto fi = f(sample);
            if(!std::isnan(fi)){
                mySum += fi;
                mySumSquared += fi * fi;
            }
        }

        if(rank != 0){
            MPI_Send(&mySum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
            MPI_Send(&mySumSquared, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
        } else {
            for (int i = 1; i < size; ++i) {
                double temp1, temp2;
                MPI_Recv(&temp1, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&temp2, 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                mySum += temp1;
                mySumSquared += temp2;
            }
        }

        MPI_Barrier(MPI_COMM_WORLD);

        if(rank == 0){
            integral = domain->getModOmega() * mySum / N;
            variance = domain->getModOmega() * domain->getModOmega() * ((mySumSquared - (mySum * mySum) / N) / (N - 1)) / N;
        }

    };

    double getIntegral() const { return integral; }
    double getVariance() const { return variance; }

private:
    double integral;
    double variance;

};
