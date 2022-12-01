//
// Created by danie on 29/11/2022.
//

/* input file is formatted:
 * first line: domain dimension
 * other n lines: bounds for each dimension
 * */

#include "IntegrationDomain.h"

int main(int argc, char** argv){

    if(argc != 2 ) return -1;

    IntegrationDomain domain(argv[1]);

    return 0;
}
