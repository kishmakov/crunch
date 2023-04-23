#include "activation_functions.h"
#include "Neuron.h"

namespace network {

const size_t Neuron::INPUTS_NUMBER = 5;

std::vector<double> Neuron::getWeights() const {
    std::vector<double> result;
    result.reserve(INPUTS_NUMBER);

    for (size_t id = 0; id < INPUTS_NUMBER; ++id) {
        result.push_back(weights_[id]);
    }

    return result;
}

void Neuron::react(const double** inputs) {
    double sum = 0;

    const double* weight = weights_;
    const double** input = inputs;

    for (size_t inputId = 0; inputId < INPUTS_NUMBER; ++inputId) {
        sum += *weight++ * **input++;
    }

    value = sigmoid(sum);
    derivative = value * (1 - value);
}

std::vector<double> Neuron::backPropagationWeights(double delta, const double* const* inputs) const {
    std::vector<double> result;
    result.reserve(INPUTS_NUMBER);

    const double* const* input = inputs;
    delta *= derivative;

    for (size_t linkId = 0; linkId < INPUTS_NUMBER; ++linkId) {
        result.push_back(delta * **input++);
    }

    return result;
}

std::vector<double> Neuron::backPropagationInputs(double delta) const {
    std::vector<double> result;
    result.reserve(INPUTS_NUMBER);

    const double* weight = weights_;
    delta *= derivative;

    for (size_t linkId = 0; linkId < INPUTS_NUMBER; ++linkId) {
        result.push_back(delta * *weight++);
    }

    return result;
}

} // network