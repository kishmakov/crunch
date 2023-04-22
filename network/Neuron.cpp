#include "activation_functions.h"
#include "Neuron.h"

namespace network {

const uint64_t Neuron::INPUTS_NUMBER = 5;

void Neuron::react(const double** inputs) {
    double sum = 0;

    const double* weight = weights_;
    const double** input = inputs;

    for (unsigned inputId = 0; inputId < INPUTS_NUMBER; ++inputId) {
        sum += *weight++ * **input++;
    }

    value = sigmoid(sum);
}

} // network