//
// Created by danie on 02/12/2022.
//

#include <functional>
#include <vector>
#include <cmath>
#include <string>
#include "Geometry.hpp"
#include "mpi.h"
#include "muParser.h"
#include <omp.h>

class Montecarlo {
    public:
        Montecarlo() = default;
        
        void integrate(std::shared_ptr<Geometry> domain, long N){
            int rank, size;

            MPI_Comm_rank(MPI_COMM_WORLD, &rank);
            MPI_Comm_size(MPI_COMM_WORLD, &size);

            MPI_Bcast(&N, 1, MPI_LONG, 0, MPI_COMM_WORLD);

            const long mySamples = N / size + (rank < (N % size));
            double mySum = 0.;
            double mySumSquared = 0.;
            std::vector<double> sample(domain->getNDimensions());

            //Parser initialization
            mu::Parser parser;
            parser.SetExpr(domain->getFunction());

            #pragma omp parallel for num_threads(12) default(none) lastprivate(sample) firstprivate(mySamples, domain, rank, parser) reduction(+ : mySum , mySumSquared)
            for (int i = 0; i < mySamples; ++i) {
                sample = domain->generatePoint();

                for (int j = 0; j < domain->getNDimensions(); ++j) {
                    std::string arg = "x";
                    arg += std::to_string(j + 1);
                    parser.DefineVar(arg, &sample.at(j));
                }

                auto fi = parser.Eval();

                mySum += fi;
                mySumSquared += fi * fi;
            }

            double sum = 0, sumSquared = 0;
            MPI_Reduce(&mySum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            MPI_Reduce(&mySumSquared, &sumSquared, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

            if(rank == 0){
                integral = domain->getModOmega() * sum / N;
                variance = domain->getModOmega() * domain->getModOmega() * ((sumSquared - (sum * sum) / N) / (N - 1)) / N;
            }
        };

        double getIntegral() const { return integral; }
        double getVariance() const { return variance; }

    private:
        double integral;
        double variance;
};
