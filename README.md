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