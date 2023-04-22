#include "NetworkComputation.h"
#include "activation_functions.h"

namespace network {

NetworkComputation::NetworkComputation(const Case& kase, const Weights& weights) :
        case_(kase),
        weights_(weights) {
    for (unsigned neuronId = 0; neuronId < 5; ++neuronId) {
        double x = 0;

        unsigned lowId = neuronId * 5;
        unsigned highId = neuronId * 5 + 5;

        for (unsigned weightId = lowId; weightId < highId; ++weightId) {
            x += getInput(weightId) * weights_[weightId];
        }

        actual_[neuronId] = network::sigmoid(x);
    }
}

Weights NetworkComputation::backPropagation() const {
    Weights weightDeltas = Weights::zeroed();

    std::vector<double> actualDeltas = std::vector<double>(5, 0.0);

    actualDeltas[5 - 1] = getActual() - case_.getTarget();

    for (unsigned neuronId = 5; neuronId > 0; ) {
        --neuronId;

        unsigned lowId = neuronId * 5;

        double actual = getActual(neuronId);
        double derivative = actualDeltas[neuronId] * actual * (1 - actual);

        for (unsigned linkId = 0; linkId < 5; ++linkId) {
            if (neuronId + 1 == 5 && linkId < 4) {
                actualDeltas[linkId] = derivative * weights_[lowId + linkId];
            }

            weightDeltas[lowId + linkId] += derivative * getInput(lowId + linkId);
        }
    }

    return std::move(weightDeltas);
}

double NetworkComputation::getActual(unsigned id) const {
    if (id >= 5) {
        throw std::out_of_range("Index out of range");
    }

    return actual_[id];
}

} // network