#!/bin/bash
# A script to automate NIST testing and generate all result reports
# Author: Tejas Sharma

mkdir -p reports/
cd generate_data/
echo "Generating random bits"
if [[ -n $CXX ]]; then
    if [[ -n $CXXFLAGS ]]; then
        $CXX $CXXFLAGS generator.cpp -o generator
    else
        $CXX generator.cpp -o generator
    fi
else
    g++ generator.cpp -o generator
fi
rm -rf *.dSYM
head -c 48000000 /dev/random > random
./generator
rm generator
cd ..

file="generate_data/random"
echo "0" > input.txt
echo "../${file}" >> input.txt
echo "1" >> input.txt
echo "0" >> input.txt
echo "128" >> input.txt
echo "1" >> input.txt
cd sts/
echo "Testing random using NIST suite"
./assess 3000000 < ../input.txt > /dev/null
cp experiments/AlgorithmTesting/finalAnalysisReport.txt ../reports/random_finalAnalysisReport.txt
cd ../

for operator in add sub mul div mod or and xor not; do
    file="generate_data/${operator}_results"
    echo "0" > input.txt
    echo "../${file}" >> input.txt
    echo "1" >> input.txt
    echo "0" >> input.txt
    echo "128" >> input.txt
    echo "1" >> input.txt
    cd sts/
    echo "Testing ${operator} using NIST suite"
    ./assess 1500000 < ../input.txt > /dev/null
    cp experiments/AlgorithmTesting/finalAnalysisReport.txt ../reports/${operator}_finalAnalysisReport.txt
    cd ../
done

rm input.txt
cd generate_data/
rm *_results
rm random
cd ../
echo "All tests completed and reports generated."
