#include <iostream>
#include <memory>
#include "component.h"
#include "circuit.h"
#include "nodal_simulator.h"
#include "analysis.h"

using namespace std;

void clearterminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    int numofnodes, choice;
    cout << "Enter the number of Non Ground Nodes: ";
    cin >> numofnodes;
    Circuit myCircuit(numofnodes);
    while(1) {
        clearterminal();
        cout << "Choose an Option:" << endl;
        cout << "1. Add Component " << endl;
        cout << "2. Start Analysis" << endl;
        cout << "3. Exit Program" << endl;
        cout << "Select Option: ";
        cin >> choice;
        if (choice == 3) return 0;
        else if (choice == 2) {
            break;
        }
        else if (choice == 1) {
            string n;
            int type, x, y;
            double val;
            clearterminal();
            cout << "Choose Component:" << endl;
            cout << "1. Resistor" << endl;
            cout << "2. Capacitor" << endl;
            cout << "3. Inductor" << endl;
            cout << "4. Voltage Source" << endl;
            cout << "Choose Option: "; cin >> type; cout << endl;
            cout << "Enter component name: ";
            cin >> n;
            cout << "Enter first node: ";
            cin >> x;
            cout << "Enter second node: ";
            cin >> y;
            cout << "Enter value: ";
            cin >> val;
            if (x < 0 || y < 0 || x > numofnodes || y > numofnodes) continue;
            switch (type) {
                case 1:
                    myCircuit.addComponent(
                        make_unique<Resistor>(n, x, y, val)
                    );
                    break;
                case 2:
                    myCircuit.addComponent(
                        make_unique<Capacitor>(n, x, y, val)
                    );
                    break;
                case 3:
                    myCircuit.addComponent(
                        make_unique<Inductor>(n, x, y, val)
                    );
                    break;
                case 4:
                    myCircuit.addComponent(
                        make_unique<VoltageSource>(n, x, y, val)
                    );
                    break;
                default:
                    cout << "Invalid component option!" << endl;
                    system("pause");
                    continue;
            }
            cout << "\nComponent added successfully.";
            system("pause");
        }
        else {
            cout << "Invalid option!" << endl;
            system("pause");
        }
    }

    auto simulator = make_shared<NodalSimulator>();

    int analysisType;

    clearterminal();

    cout << "Choose Analysis Type:" << endl;
    cout << "1. DC Analysis" << endl;
    cout << "2. AC Analysis" << endl;
    cout << "Select Option: ";
    cin >> analysisType;

    if (analysisType == 1) {
        clearterminal();
        DCAnalysis dc(simulator);
        dc.run(myCircuit);
    }

    else if (analysisType == 2) {
        double startFreq, stopFreq, multiplier;
        clearterminal();
        cout << "Enter Start Frequency (Hz): ";
        cin >> startFreq;
        cout << "Enter Stop Frequency (Hz): ";
        cin >> stopFreq;
        cout << "Enter Frequency Multiplication Factor: ";
        cin >> multiplier;
        if (startFreq <=0 || stopFreq <= 0 || startFreq > stopFreq || multiplier <= 1) {cout << "Invalid Freq"; return 0;}
        clearterminal();
        ACAnalysis ac(simulator, startFreq, stopFreq, multiplier);
        ac.run(myCircuit);
    }
    else {
        cout << "Invalid analysis option!" << endl;
    }
    return 0;
}