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

class Montecarlo {
    public:
        Montecarlo() = default;
        
        void integrate(Geometry* domain, long N){
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

                #pragma omp parallel for default(none) lastprivate(sample) firstprivate(mySamples, domain, rank, parser) reduction(+ : mySum , mySumSquared)
                for (int i = 0; i < mySamples; ++i) {
                    sample = domain->generatePoint(i);

                    char x = 'x';
                    for (int j = 0; j < domain->getNDimensions(); ++j) {
                        std::string arg(1, x);
                        arg += std::to_string(j + 1);
                        parser.DefineVar(arg, &sample.at(j));
                    }

                    auto fi = parser.Eval();

                    if(!std::isnan(fi)){
                        mySum += fi;
                        mySumSquared += fi * fi;
                    }
                }

                // I am not sure if you can have the send buffer equal to the receive buffer,
                // but I do not see why not. If it does not work use a different variable for
                // the reception.
                MPI_Reduce(&mySum,&mySum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
                MPI_Reduce(&mySumSquared,&mySumSquared,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
 /*           if(rank != 0){
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
*/
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
