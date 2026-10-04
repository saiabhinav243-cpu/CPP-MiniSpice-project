#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <memory>

using namespace std;
#include<Eigen/Dense>
using Complex = complex<double>;
using Matrix = vector<vector<Complex>>;
using Vector = vector<Complex>;

class Component {
protected:
    string name;
    int nodeA, nodeB;
public:
    Component(string n, int a, int b) : name(n), nodeA(a), nodeB(b) {}
    virtual Complex getImpedance(double freq) const = 0;
    virtual double getValue() const = 0;
    virtual string getType() const = 0;
    virtual bool isVoltageSource() const { return false; }
    int getNodeA() const { return nodeA; }
    int getNodeB() const { return nodeB; }
};

class Resistor : public Component {
    double resistance;
public:
    Resistor(string n, int a, int b, double r) : Component(n, a, b), resistance(r) {}
    Complex getImpedance(double freq) const override { return {resistance, 0}; }
    string getType() const override { return "R"; }
    double getValue() const override { return resistance; }
};

class Capacitor : public Component {
    double capacitance;
public:
    Capacitor(string n, int a, int b, double c) : Component(n, a, b), capacitance(c) {}
    Complex getImpedance(double freq) const override {
        if (freq == 0.0) return {1e9, 0}; 
        return {0, -1.0 / (2 * M_PI * freq * capacitance)};
    }
    string getType() const override { return "C"; }
    double getValue() const override { return capacitance; }
};

class Inductor : public Component {
double inductance;
public:
Inductor(string n, int a, int b, double l) : Component (n, a, b), inductance(l) {}
Complex getImpedance(double freq) const override {
	if (freq == 0.0) return {1e-9, 0};
	return {0, (1.0*2*M_PI*freq*inductance)};
}
string getType() const override {return "L"; }
double getValue() const override { return inductance; }
};

class VoltageSource : public Component {
    double voltage;
public:
    VoltageSource(string n, int a, int b, double v) : Component(n, a, b), voltage(v) {}
    Complex getImpedance(double freq) const override { return {0, 0}; }
    string getType() const override { return "V"; }
    double getValue() const override { return voltage; }
    bool isVoltageSource() const override { return true; }
};

class Circuit {
    vector<unique_ptr<Component>> components;
    int numNodes = 0;
public:
    void addComponent(unique_ptr<Component> comp) {
        if (comp->getNodeA() > numNodes){
	       	numNodes = comp->getNodeA();
	}
        if (comp->getNodeB() > numNodes){
	       	numNodes = comp->getNodeB();
	}
        components.push_back(move(comp));
    }
    int getNumNodes() const { return numNodes; }
    const auto& getComponents() const { return components; }
};

class NodalSimulator {
public:
    Eigen::VectorXcd solve(
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
};
 
int main() {
    Circuit myCircuit;
    myCircuit.addComponent(make_unique<VoltageSource>("V1", 1, 0, 5.0));
    myCircuit.addComponent(make_unique<Resistor>("R1", 1, 2, 100.0));
    myCircuit.addComponent(make_unique<Resistor>("R2" ,2,3,100.0));
    myCircuit.addComponent(make_unique<Resistor>("R3" ,3,0,100.0));			    
    myCircuit.addComponent(make_unique<Capacitor>("C1" ,2,3,0.00001)); 
    myCircuit.addComponent(make_unique<Inductor>("L1", 3, 0, 0.01));

    NodalSimulator simulator;
    Eigen::VectorXcd results = simulator.solve(myCircuit,0.0 );

    for (int i = 0; i < myCircuit.getNumNodes(); ++i) {
        cout << "Node " << (i + 1) << ": " << real(results[i]) << " V\n";
    }
    cout << "I_V1: " << real(results[myCircuit.getNumNodes()]) << " A\n";
    return 0;
}
