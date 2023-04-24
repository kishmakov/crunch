#ifndef CRUNCH_NEURON_H
#define CRUNCH_NEURON_H

#include <vector>

#include "math/activation_functions.h"

namespace network {

struct Neuron {
    const static size_t INPUTS_NUMBER;

    explicit Neuron(const double* weights, const math::ActivationFunction& af) : weights_(weights), af_(af) {}

    [[nodiscard]] std::vector<double> getWeights() const;

    void react(const double** inputs);

    [[nodiscard]]
    std::vector<double> backPropagationWeights(double delta, const double* const* inputs) const;

    [[nodiscard]] std::vector<double> backPropagationInputs(double delta) const;

    double value = 0;

private:
    double derivative = 0;
    const double* weights_;
    const math::ActivationFunction& af_;
};

} // network

#endif //CRUNCH_NEURON_H
