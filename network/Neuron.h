#ifndef CRUNCH_NEURON_H
#define CRUNCH_NEURON_H

#include <vector>

namespace network {

struct Neuron {
    const static uint64_t INPUTS_NUMBER;

    explicit Neuron(const double* weights) : weights_(weights) {}

    void react(const double** inputs);

    double value = 0;

private:
    const double* weights_;
};


} // network

#endif //CRUNCH_NEURON_H
