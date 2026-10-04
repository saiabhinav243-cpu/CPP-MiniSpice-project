#ifndef NODAL_SIMULATOR_H
#define NODAL_SIMULATOR_H

#include "Circuit.h"
#include <Eigen/Dense>

class NodalSimulator {
public:
    Eigen::VectorXcd solve(
        const Circuit& circuit,
        double freq
    );
};

#endif