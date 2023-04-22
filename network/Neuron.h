#ifndef CRUNCH_NEURON_H
#define CRUNCH_NEURON_H

#include <vector>

namespace network {

struct Neuron {
    explicit Neuron(double* weights) : weights_(weights) {}

    void act(std::vector<double*> inputs);

    double value = 0;
    double delta = 0;

private:
    std::vector<double*> inputs_;
    double* weights_;
};


} // network

#endif //CRUNCH_NEURON_H
