# MontecarloProject

In order to use the Montecarlo Algorithm, you should download the repo and then perform the following commands from your terminal
```
cd muparser-2.3.4/
cmake . -DENABLE_SAMPLES=OFF -DENABLE_OPENMP=ON -DENABLE_WIDE_CHAR=OFF -DBUILD_SHARED_LIBS=ON
make
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/jellyfish/shared-folder/MontecarloProject/muparser-2.3.4
```

To use the muparser library, you should include it when compiling the program as follow:
```
g++ -I../muparser-2.3.4/include prova.cpp -o prova -L../muparser-2.3.4 -lmuparser
./prova
```

Command line arguments
---
```
Domain type: 
    0- Hyper-Rectangle
    1- Hyper-Sphere
Number of samples
Input file path
```

Input file arguments
---
```
First row: Function used
Second row: Domain dimension
In case of Hyper-Rectangle - successive rows:
    Extreme values for each bounds
In case of Hyper-Sphere - successive row:
    Hyper-sphere's centre and radius
```