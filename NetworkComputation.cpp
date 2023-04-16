#include "NetworkComputation.h"
#include "activation_functions.h"

const uint64_t NetworkComputation::NEURONS_NUMBER = 5;

NetworkComputation::NetworkComputation(const Case& kase, const Weights& weights) :
        case_(kase),
        weights_(weights) {
    for (unsigned neuronId = 0; neuronId < NEURONS_NUMBER; ++neuronId) {
        double x = 0;

        unsigned lowId = neuronId * 5;
        unsigned highId = neuronId * 5 + 5;

        for (unsigned weightId = lowId; weightId < highId; ++weightId) {
            x += getInput(weightId) * weights_[weightId];
        }

        actual_[neuronId] = sigmoid(x);
    }
}

Weights NetworkComputation::backPropagation() const {
    Weights weightDeltas = Weights::zeroed();

    std::vector<double> actualDeltas = std::vector<double>(NEURONS_NUMBER, 0.0);

    actualDeltas[NEURONS_NUMBER - 1] = getActual() - case_.getTarget();

    for (unsigned neuronId = NEURONS_NUMBER; neuronId > 0; ) {
        --neuronId;

        unsigned lowId = neuronId * 5;

        double actual = getActual(neuronId);
        double derivative = actualDeltas[neuronId] * actual * (1 - actual);

        for (unsigned linkId = 0; linkId < 5; ++linkId) {
            if (neuronId + 1 == NEURONS_NUMBER && linkId < 4) {
                actualDeltas[linkId] = derivative * weights_[lowId + linkId];
            }

            weightDeltas[lowId + linkId] += derivative * getInput(lowId + linkId);
        }
    }

    return std::move(weightDeltas);
}

double NetworkComputation::getActual(unsigned id) const {
    if (id >= NEURONS_NUMBER) {
        throw std::out_of_range("Index out of range");
    }

    return actual_[id];
}