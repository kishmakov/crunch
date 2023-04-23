#ifndef CRUNCH_NEURON_H
#define CRUNCH_NEURON_H

#include <vector>

namespace network {

struct Neuron {
    const static size_t INPUTS_NUMBER;

    explicit Neuron(const double* weights) : weights_(weights) {}

    [[nodiscard]] std::vector<double> getWeights() const;

    void react(const double** inputs);

    [[nodiscard]]
    std::vector<double> backPropagationWeights(double delta, const double* const* inputs) const;

    [[nodiscard]] std::vector<double> backPropagationInputs(double delta) const;

    double value = 0;

private:
    double derivative = 0;
    const double* weights_;
};


} // network

#endif //CRUNCH_NEURON_H
