#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "circuit.h"
#include <vector>
#include <complex>

using namespace std;

class ISimulator {
public:
    virtual ~ISimulator() = default;
    virtual vector<complex<double>> solve(const Circuit& circuit, double frequency) = 0; 
};

#endif