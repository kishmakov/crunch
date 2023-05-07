#include "Neuron.h"

namespace network {

const size_t Neuron::INPUTS_NUMBER = 5;

Neuron::Neuron(const std::string& funcName) :
    weights_(nullptr),
    af_(math::activationByName(funcName))
{}

std::vector<double> Neuron::getWeights() const {
    std::vector<double> result;
    result.reserve(INPUTS_NUMBER);

    for (size_t id = 0; id < INPUTS_NUMBER; ++id) {
        result.push_back(weights_[id]);
    }

    return result;
}

void Neuron::init(double* weights) {
    weights_ = weights;
}

void Neuron::shuffle() {
    if (weights_ == nullptr) {
        throw std::runtime_error("shuffle requires neuron initialisation");
    }

    double* weight = weights_;
    for (size_t inputId = 0; inputId < INPUTS_NUMBER; ++inputId) {
        *weight++ = af_.init(inputId);
    }
}


void Neuron::react(const double** inputs) {
    if (weights_ == nullptr) {
        throw std::runtime_error("react requires neuron initialisation");
    }

    double sum = 0;

    const double* weight = weights_;
    const double** input = inputs;

    for (size_t inputId = 0; inputId < INPUTS_NUMBER; ++inputId) {
        sum += *weight++ * **input++;
    }

    value = af_.function(sum);
    derivative = af_.derivative(sum);
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