#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "circuit.h"
#include "simulator.h"
#include <memory>
#include <vector>

using namespace std;

class IAnalysis {
protected:
    shared_ptr<ISimulator> simulator;
public:
    IAnalysis(shared_ptr<ISimulator> sim) : simulator(move(sim)) {}
    virtual ~IAnalysis() {};
    virtual void run(const Circuit& ckt) = 0; 
};

class DCAnalysis : public IAnalysis {
public:
    DCAnalysis(shared_ptr<ISimulator> sim) : IAnalysis(move(sim)) {}
    void run(const Circuit& ckt) override; 
};

class ACAnalysis : public IAnalysis {
    double startFreq;
    double endFreq;
    double step;
public:
    ACAnalysis(shared_ptr<ISimulator> sim, double start, double end, double stepSize) : IAnalysis(move(sim)), startFreq(start), endFreq(end), step(stepSize) {} 
    void run(const Circuit& ckt) override;
};

#endif