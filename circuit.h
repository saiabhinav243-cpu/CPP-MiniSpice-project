#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "component.h"
#include <vector>
#include <memory>

using namespace std;

class Circuit {
    vector<unique_ptr<Component>> components;
    int numNodes = 0;
    int groundNode = 0; 
public:
    Circuit() = default;
    Circuit(int nodes) : numNodes(nodes), groundNode(0) {} 

    void addComponent(unique_ptr<Component> comp);
    int getNumNodes() const;
    int getGroundNode() const { return groundNode; }
    const vector<unique_ptr<Component>>& getComponents() const;
};

#endif