#include <iostream>
#include <memory>
#include "component.h"
#include "circuit.h"
#include "nodal_simulator.h"
#include "circuit_visualizer.h"

using namespace std;

int main() {
    Circuit myCircuit;
    myCircuit.addComponent(make_unique<VoltageSource>("V1", 1, 0, 5.0));
    myCircuit.addComponent(make_unique<Resistor>("R1", 1, 2, 100.0));
    myCircuit.addComponent(make_unique<Resistor>("R2", 2, 3, 100.0));
    myCircuit.addComponent(make_unique<Resistor>("R3", 3, 0, 100.0));            
    myCircuit.addComponent(make_unique<Capacitor>("C1", 2, 3, 0.00001)); 
    myCircuit.addComponent(make_unique<Inductor>("L1", 3, 0, 0.01));

    CircuitVisualizer::exporttodot(myCircuit, "circuit.dot");
    CircuitVisualizer::rendertoimage("circuit.dot", "circuit.png", "png");

    NodalSimulator simulator;
    Eigen::VectorXcd results = simulator.solve(myCircuit, 0.0);

    for (int i = 0; i < myCircuit.getNumNodes(); ++i) {
        cout << "Node " << (i + 1) << ": " << real(results[i]) << " V\n";
    }
    cout << "I_V1: " << real(results[myCircuit.getNumNodes()]) << " A\n";

    return 0;
}