#include "analysis.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>

using namespace std;

void DCAnalysis::run(const Circuit& ckt) {
    cout << "\nDC Analysis\n\n\n";
    auto results = simulator->solve(ckt, 0.0); 

    cout << "Node Voltages:\n";
    for (int i = 0; i < ckt.getNumNodes(); ++i) {
        cout << "V(" << (i + 1) << ") = " << fixed << setprecision(3) << results[i].real() << " V\n";
    }

    cout << "\nComponent Currents:\n";
    int v_idx = ckt.getNumNodes();
    for (const auto& comp : ckt.getComponents()) {
        if (comp->isVoltageSource()) {
            cout << "I(" << comp->getName() << ") = " << fixed << setprecision(3) 
                 << results[v_idx].real() * 1000.0 << " mA\n";
            v_idx++;
        } else {
            complex<double> vA = (comp->getNodeA() == 0) ? 0.0 : results[comp->getNodeA() - 1];
            complex<double> vB = (comp->getNodeB() == 0) ? 0.0 : results[comp->getNodeB() - 1];
            complex<double> current = (vA - vB) / comp->getImpedance(0.0);
            
            cout << "I(" << comp->getName() << ") = " << fixed << setprecision(3) 
                 << current.real() * 1000.0 << " mA\n";
        }
    }
}

void ACAnalysis::run(const Circuit& ckt) {
    cout << "\nAC Analysis\n\n\n";
    
    cout << left << setw(25) << "Frequency";
    for (int i = 1; i <= ckt.getNumNodes(); ++i) {
        cout << setw(36) << ("V(" + to_string(i) + ")");
    }
    cout << "\n";

    for (double f = startFreq; f <= endFreq; f *= step) { 
        auto results = simulator->solve(ckt, f);
        
        if (f < 1000) cout << left << setw(9) << fixed << setprecision(0) << f << setw(3) << "Hz";
        else cout << left << setw(9) << fixed << setprecision(1) << (f/1000) << setw(3) << "kHz";

        for (int i = 0; i < ckt.getNumNodes(); ++i) {
            double mag = abs(results[i]);
            double phase = arg(results[i]) * 180.0 / M_PI;
            
            if (abs(phase) < 0.05) phase = 0.0;
            
            stringstream ss;
            ss << fixed << setprecision(2) << "Mag: " << mag << " Phase: " << setprecision(1) << phase << " Degrees    ";
            cout << left << setw(18) << ss.str();
        }
        cout << "\n";
    }
}