#ifndef NODAL_SIMULATOR_H
#define NODAL_SIMULATOR_H

#include "simulator.h"
#include <Eigen/Dense>
#include <vector>
#include <complex>

using namespace std;

class NodalSimulator : public ISimulator {
public:
    vector<complex<double>> solve(const Circuit& circuit, double freq) override;
};

#endif