#include "Network.h"

namespace network {

const size_t Network::NEURONS_NUMBER = 5;
const double Network::BIAS_INPUT = -1.0;


Network::Network(const Weights& weights) : weights_(weights) {
    neurons_.reserve(NEURONS_NUMBER);

    for (unsigned neuronId = 0; neuronId < NEURONS_NUMBER; ++neuronId) {
        neurons_.emplace_back(&weights_.weights_[neuronId * Neuron::INPUTS_NUMBER]);
    }
}

double Network::react(const std::vector<double>& inputs) {
    inputsPtrs_.clear();
    inputsPtrs_.reserve(2 * Neuron::INPUTS_NUMBER);

    for (const auto& input: inputs) {
        inputsPtrs_.push_back(&input);
    }

    inputsPtrs_.push_back(&BIAS_INPUT);

    for (unsigned neuronId = 0; neuronId + 1 < NEURONS_NUMBER; ++neuronId) {
        inputsPtrs_.push_back(&neurons_[neuronId].value);
        neurons_[neuronId].react(&inputsPtrs_[0]);
    }

    inputsPtrs_.push_back(&BIAS_INPUT);
    neurons_[NEURONS_NUMBER - 1].react(&inputsPtrs_[Neuron::INPUTS_NUMBER]);

    return neurons_[NEURONS_NUMBER - 1].value;
}

const Neuron& Network::getNeuron(size_t index) {
    if (index >= NEURONS_NUMBER) {
        throw std::out_of_range("Index out of range");
    }

    return neurons_[index];
}

} // network