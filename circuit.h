#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "Component.h"
#include <vector>
#include <memory>

using namespace std;

class Circuit {
    vector<unique_ptr<Component>> components;
    int numNodes = 0;
public:
    void addComponent(unique_ptr<Component> comp);
    int getNumNodes();
    const auto& getComponents();
};

#endif