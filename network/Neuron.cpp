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

std::vector<double> Neuron::getWeights() const {
    std::vector<double> result;
    result.reserve(INPUTS_NUMBER);

    for (size_t id = 0; id < INPUTS_NUMBER; ++id) {
        result.push_back(weights_[id]);
    }

    return result;
}

} // network