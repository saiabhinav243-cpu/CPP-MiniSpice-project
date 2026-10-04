#include "circuit_visualizer.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

bool CircuitVisualizer::exporttodot(const Circuit& circuit, const string& dotfilename) {
    ofstream out(dotfilename);
    if (!out.is_open()) return false;

    out << "graph CircuitGraph {\n";
    out << "    rankdir=LR;\n";
    out << "    splines=ortho;\n"; // Use clean orthogonal wires
    out << "    nodesep=0.8;\n";
    out << "    ranksep=0.8;\n\n";

    // Circuit electrical junctions (nodes)
    out << "    // Circuit Nodes\n";
    out << "    node [fontname=\"Helvetica\", fontsize=10];\n";
    out << "    \"GND\" [shape=point, width=0.25, label=\"\"];\n";
    for (int i = 1; i <= circuit.getNumNodes(); ++i) {
        out << "    \"N" << i << "\" [shape=circle, width=0.4, fixedsize=true, style=filled, fillcolor=\"#e2e8f0\", color=\"#475569\", label=\"" << i << "\"];\n";
    }
    out << "\n";

    // Components rendered as blocks with units
    out << "    // Component Blocks\n";
    int comp_id = 0;
    for (const auto& comp : circuit.getComponents()) {
        comp_id++;
        string cnode = "comp_" + to_string(comp_id);

        string unit = "";
        string color = "#334155";
        string fill = "#f8fafc";

        if (comp->getType() == "R") {
            unit = " Ω";
            color = "#d97706";
            fill = "#fef3c7";
        } else if (comp->getType() == "C") {
            unit = " F";
            color = "#2563eb";
            fill = "#dbeafe";
        } else if (comp->getType() == "L") {
            unit = " H";
            color = "#16a34a";
            fill = "#dcfce7";
        } else if (comp->isVoltageSource()) {
            unit = " V";
            color = "#dc2626";
            fill = "#fee2e2";
        }

        // Draw component as a structured label
        out << "    \"" << cnode << "\" [shape=box, style=\"rounded,filled\", color=\"" << color 
            << "\", fillcolor=\"" << fill << "\", penwidth=1.5, label=\"" 
            << comp->getName() << "\\n" << comp->getValue() << unit << "\"];\n";

        // Connect nodes to component
        string nodeA = (comp->getNodeA() == 0) ? "\"GND\"" : "\"N" + to_string(comp->getNodeA()) + "\"";
        string nodeB = (comp->getNodeB() == 0) ? "\"GND\"" : "\"N" + to_string(comp->getNodeB()) + "\"";

        out << "    " << nodeA << " -- \"" << cnode << "\" [color=\"#64748b\", penwidth=1.2];\n";
        out << "    \"" << cnode << "\" -- " << nodeB << " [color=\"#64748b\", penwidth=1.2];\n";
    }

    out << "}\n";
    out.close();
    return true;
}

bool CircuitVisualizer::rendertoimage(const string& dotfilename, const string& outputfilename, const string& format) {
    string command = "dot -T" + format + " " + dotfilename + " -o " + outputfilename;
    int ret = system(command.c_str());
    if (ret != 0) {
        cerr << "Failed to render graph. Make sure Graphviz is installed and 'dot' is in PATH.\n";
        return false;
    }
    cout << "Rendered circuit diagram: " << outputfilename << "\n";
    return true;
}