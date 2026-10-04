#include "component.h"
#include <cmath>
using namespace std;

Resistor::Resistor(string n, int a, int b, double r) : Component(n, a, b), resistance(r) {}
Complex Resistor::getImpedance(double freq) const { return Complex(resistance, 0); }
string Resistor::getType() const { return "R"; }
double Resistor::getValue() const { return resistance; }


Capacitor::Capacitor(string n, int a, int b, double c) : Component(n, a, b), capacitance(c) {}
Complex Capacitor::getImpedance(double freq) const {
    if (freq == 0.0) return Complex(1e9, 0); 
    return Complex(0, -1.0 / (2 * M_PI * freq * capacitance));
}
string Capacitor::getType() const { return "C"; }
double Capacitor::getValue() const { return capacitance; }

Inductor::Inductor(string n, int a, int b, double l) : Component (n, a, b), inductance(l) {}
Complex Inductor::getImpedance(double freq) const {
	if (freq == 0.0) return Complex(1e-9, 0);
	return Complex(0, (1.0*2*M_PI*freq*inductance));
}
string Inductor::getType() const {return "L"; }
double Inductor::getValue() const { return inductance; }

VoltageSource::VoltageSource(string n, int a, int b, double v) : Component(n, a, b), voltage(v) {}
Complex VoltageSource::getImpedance(double freq) const { return Complex(0, 0); }
string VoltageSource::getType() const { return "V"; }
double VoltageSource::getValue() const { return voltage; }
bool VoltageSource::isVoltageSource() const { return true; }