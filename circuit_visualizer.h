#ifndef CIRCUIT_VISUALIZER_H
#define CIRCUIT_VISUALIZER_H

#include "circuit.h"
#include <string>

using namespace std;

class CircuitVisualizer {
    public:
        static bool exporttodot(const Circuit& circuit, const string& dotfilename);
        static bool rendertoimage(const string& dotfilename, const string& outputfilename, const string& format = "png");
};

#endif