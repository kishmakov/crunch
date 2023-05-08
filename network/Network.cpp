#include "Network.h"

#include <utility>

namespace network {

const size_t Network::NEURONS_NUMBER = 5;
const double Network::BIAS_INPUT = 1.0;

Network::Network(const std::string& scheme) :
        weights_(NEURONS_NUMBER * Neuron::INPUTS_NUMBER)
{
    buildNeurons(scheme);
    initNeurons();
}

Network::Network(const std::string& scheme, Weights weights) :
    weights_(std::move(weights))
{
    if (weights_.size() != NEURONS_NUMBER * Neuron::INPUTS_NUMBER) {
        throw std::runtime_error("wrong weights provided");
    }

    buildNeurons(scheme);
    initNeurons();
}

const Neuron& Network::getNeuron(size_t index) const {
    if (index >= NEURONS_NUMBER) {
        throw std::out_of_range("Index out of range");
    }

    return neurons_[index];
}

std::vector<const double*> Network::getInputPtrs(const std::vector<double>& inputs) const {
    std::vector<const double*> result;
    result.reserve(2 * Neuron::INPUTS_NUMBER);

    for (const auto& input: inputs) {
        result.push_back(&input);
    }

    result.push_back(&BIAS_INPUT);

    for (size_t neuronId = 0; neuronId + 1 < NEURONS_NUMBER; ++neuronId) {
        result.push_back(&neurons_[neuronId].value);
    }

    result.push_back(&BIAS_INPUT);

    return result;
}

void Network::init(Weights weights) {
    weights_ = std::move(weights);
    initNeurons();
}

void Network::initNeurons() {
    for (size_t neuronId = 0; neuronId < NEURONS_NUMBER; ++neuronId) {
        neurons_[neuronId].init(weights_.startForNeuron(neuronId));
    }
}

void Network::shuffle() {
    for (auto& neuron: neurons_) {
        neuron.shuffle();
    }
}

double Network::react(const std::vector<double>& inputs) {
    auto inputsPtrs = getInputPtrs(inputs);

    for (size_t neuronId = 0; neuronId + 1 < NEURONS_NUMBER; ++neuronId) {
        neurons_[neuronId].react(&inputsPtrs[0]);
    }

    neurons_[NEURONS_NUMBER - 1].react(&inputsPtrs[Neuron::INPUTS_NUMBER]);
    return neurons_[NEURONS_NUMBER - 1].value;
}

Weights Network::backPropagation(double delta, const std::vector<double>& inputs) const {
    auto inputsPtrs = getInputPtrs(inputs);
    auto deltas = neurons_[NEURONS_NUMBER - 1].backPropagationInputs(delta);
    deltas[NEURONS_NUMBER - 1] = delta;

    std::vector<double> result;
    result.reserve(NEURONS_NUMBER * Neuron::INPUTS_NUMBER);

    size_t neuronId = 0;

    for (const auto& neuron: neurons_) {
        const double* const* inputs = (neuronId + 1 < NEURONS_NUMBER)
                ? &inputsPtrs[0]
                : &inputsPtrs[Neuron::INPUTS_NUMBER];

        auto partial = neuron.backPropagationWeights(deltas[neuronId], inputs);
        result.insert(result.end(), partial.begin(), partial.end());

        ++neuronId;
    }

    return Weights(std::move(result));
}

Network& Network::operator+=(const Weights& correction) {
    weights_ += correction;
    return *this;
}

void Network::buildNeurons(const std::string& scheme) {
    const auto& pack = math::packByName(scheme);

    for (size_t neuronId = 0; neuronId < NEURONS_NUMBER; ++neuronId) {
        neurons_.emplace_back(pack[neuronId]);
    }
}

} // network