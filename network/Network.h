#ifndef CRUNCH_NETWORK_H
#define CRUNCH_NETWORK_H

#include "Neuron.h"
#include "Weights.h"

namespace network {

struct Network {
    const static size_t NEURONS_NUMBER;

    explicit Network(const Weights& weights);

    [[nodiscard]]
    const Neuron& getNeuron(size_t index) const;

    double react(const std::vector<double>& inputs);

    [[nodiscard]]
    Weights backPropagation(double delta, const std::vector<double>& inputs) const;

private:
    const static double BIAS_INPUT;

    [[nodiscard]]
    std::vector<const double*> getInputPtrs(const std::vector<double>& inputs) const;

    const Weights& weights_;
    std::vector<Neuron> neurons_;
};

} // network

#endif //CRUNCH_NETWORK_H
