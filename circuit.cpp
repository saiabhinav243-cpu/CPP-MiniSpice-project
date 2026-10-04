#include "circuit.h"

void Circuit::addComponent(unique_ptr<Component> comp) {
    if (comp->getNodeA() > numNodes){
	    numNodes = comp->getNodeA();
}
    if (comp->getNodeB() > numNodes){
       	numNodes = comp->getNodeB();
}
    components.push_back(move(comp));
}
int Circuit::getNumNodes() const { return numNodes; }
const vector<unique_ptr<Component>>& Circuit::getComponents() const { return components; }