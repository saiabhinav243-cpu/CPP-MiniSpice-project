#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <complex>
using namespace std;

using Complex = complex<double>;


class Component {
protected:
    string name;
    int nodeA, nodeB;
public:
    Component(string n, int a, int b) : name(n), nodeA(a), nodeB(b) {}
    virtual ~Component() {};
    virtual Complex getImpedance(double freq) const = 0;
    virtual double getValue() const = 0;
    virtual string getType() const = 0;
    virtual bool isVoltageSource() const { return false; }
    int getNodeA() const { return nodeA; }
    int getNodeB() const { return nodeB; }
    string getName() const { return name;}

};

class Resistor : public Component {
    double resistance;
public:
    Resistor(string n, int a, int b, double r);
    Complex getImpedance(double freq) const override;
    string getType() const override;
    double getValue() const override;
};

class Capacitor : public Component {
    double capacitance;
public:
    Capacitor(string n, int a, int b, double c);
    Complex getImpedance(double freq) const override;
    string getType() const override;
    double getValue() const override;
};

class Inductor : public Component {
    double inductance;
public:
    Inductor(string n, int a, int b, double l);
    Complex getImpedance(double freq) const override;
    string getType() const override;
    double getValue() const override;
};

class VoltageSource : public Component {
    double voltage;
public:
    VoltageSource(string n, int a, int b, double v);
    Complex getImpedance(double freq) const override;
    string getType() const override;
    double getValue() const override;
    bool isVoltageSource() const override;
};

#endif