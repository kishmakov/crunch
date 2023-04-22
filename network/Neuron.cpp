#include "activation_functions.h"
#include "Neuron.h"

namespace network {

void Neuron::act(std::vector<double *> inputs) {
    inputs_ = std::move(inputs);

    double sum = 0;

    double* weight = weights_;

    for (double* input: inputs_) {
        sum += *weight++ * *input;
    }

    value = sigmoid(sum);
}

} // network