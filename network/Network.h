#ifndef CRUNCH_NETWORK_H
#define CRUNCH_NETWORK_H

#include "Neuron.h"
#include "Weights.h"

namespace network {

struct Network {
    explicit Network(const Weights& weights);
    double react(const std::vector<double>& inputs);

    const static size_t NEURONS_NUMBER;

    const Neuron& getNeuron(size_t index);

private:
    const static double BIAS_INPUT;

    const Weights& weights_;
    std::vector<Neuron> neurons_;
    std::vector<const double*> inputsPtrs_;
};

} // network

#endif //CRUNCH_NETWORK_H
