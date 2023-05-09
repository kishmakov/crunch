#include "Neuron.h"

namespace network {


Neuron::Neuron(const std::string& funcName, DoublePs weights) : DoublePs(std::move(weights)),
    af_(math::activationByName(funcName))
{}

void Neuron::init(double* weights) {
    for (auto& weightPointer: *this) {
        weightPointer = weights++;
    }
}

void Neuron::initInputs(DoubleCPs inputs) {
    inputs_ = std::move(inputs);
}

void Neuron::shuffle() {
    for (size_t id = 0; id < size(); ++id) {
        *at(id) = af_.init(id);
    }
}

void Neuron::react() {
    double sum = 0;

    auto input = inputs_.cbegin();

    for (size_t id = 0; id < size(); ++id) {
        sum += *at(id) * **input++;
    }

    value = af_.function(sum);
    derivative = af_.derivative(sum);
}

std::vector<double> Neuron::backPropagationWeights(double delta) const {
    std::vector<double> result(size(), 0.0);

    auto input = inputs_.begin();
    delta *= derivative;

    for (size_t id = 0; id < size(); ++id) {
        result[id] = delta * **input++;
    }

    return result;
}

std::vector<double> Neuron::backPropagationInputs(double delta) const {
    std::vector<double> result(size(), 0.0);

    delta *= derivative;

    for (size_t id = 0; id < size(); ++id) {
        result[id] = delta * *at(id);
    }

    return result;
}

} // network