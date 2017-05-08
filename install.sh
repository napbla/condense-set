#!/bin/bash
echo Compiling condense
g++ -c src/condense.cpp
g++ condense.o -o condense
echo Copy to /usr/local/bin
cp condense /usr/local/bin
echo Copy to bin folder of the project
mv condense bin
echo Clean up
rm condense.o
echo Compiling knn
g++ -c src/knn.cpp
g++ knn.o -o knn
echo Copy to /usr/local/bin
cp knn /usr/local/bin
echo Copy to bin folder of the project
mv knn bin
echo Clean up
rm knn.o
