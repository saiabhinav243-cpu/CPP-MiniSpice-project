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
int Circuit::getNumNodes() { return numNodes; }
const auto& Circuit::getComponents() const { return components; }