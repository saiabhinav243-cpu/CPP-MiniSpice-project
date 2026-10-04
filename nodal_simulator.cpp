#include "nodal_simulator.h"
using namespace std;

    Eigen::VectorXcd NodalSimulator::solve(
        const Circuit& circuit,
        double freq
    ) {

        int N = circuit.getNumNodes();


        int M = 0;

        for (const auto& comp : circuit.getComponents()) {
            if (comp->isVoltageSource())
                M++;
        }


        Eigen::MatrixXcd A =
            Eigen::MatrixXcd::Zero(N + M, N + M);

        Eigen::VectorXcd b =
            Eigen::VectorXcd::Zero(N + M);


        int v_idx = N;

        for (const auto& comp : circuit.getComponents()) {

            int nA = comp->getNodeA() - 1;
            int nB = comp->getNodeB() - 1;


            if (comp->isVoltageSource()) {

                if (nA >= 0) {
                    A(nA, v_idx) += 1.0;
                    A(v_idx, nA) += 1.0;
                }

                if (nB >= 0) {
                    A(nB, v_idx) -= 1.0;
                    A(v_idx, nB) -= 1.0;
                }

                b(v_idx) = comp->getValue();

                v_idx++;
            }


            else {

                complex<double> Y =
                    1.0 / comp->getImpedance(freq);

                if (nA >= 0)
                    A(nA, nA) += Y;

                if (nB >= 0)
                    A(nB, nB) += Y;

                if (nA >= 0 && nB >= 0) {
                    A(nA, nB) -= Y;
                    A(nB, nA) -= Y;
                }
            }
        }

        // Solve A*x = b
        return A.colPivHouseholderQr().solve(b);
    }