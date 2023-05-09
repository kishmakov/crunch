#ifndef CRUNCH_NEURON_H
#define CRUNCH_NEURON_H

#include <vector>

#include "math/activation_functions.h"

namespace network {

typedef std::vector<double*> DoublePs;
typedef std::vector<const double*> DoubleCPs;

struct Neuron : DoublePs {
    Neuron(const std::string& funcName, DoublePs weights);

    void init(double* weights);
    void initInputs(DoubleCPs inputs);

    void shuffle();
    void react();

    [[nodiscard]]
    std::vector<double> backPropagationWeights(double delta) const;

    [[nodiscard]] std::vector<double> backPropagationInputs(double delta) const;

    double value = 0;

private:
    double derivative = 0;
    DoubleCPs inputs_;
    const math::ActivationFunction& af_;
};

} // network

#endif //CRUNCH_NEURON_H
