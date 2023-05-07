#include <fstream>
#include <iomanip>

#include "math/metrics.h"
#include "Neuron.h"
#include "Weights.h"

namespace network {

const size_t Weights::SIZE = 25;

[[maybe_unused]] inline std::string fullWeightsName(const std::string& scheme) { return "results/" + scheme + ".txt"; }

Weights Weights::zeroed() {
    std::vector<double> weights(SIZE, 0.0);
    return Weights(std::move(weights));
}

Weights Weights::loadFromFile(const std::string& baseName) {
    std::vector<double> weights;
    std::ifstream fin(fullWeightsName(baseName));

    double weight;

    while (fin >> weight) {
        weights.push_back(weight);
    }

    fin.close();

    return Weights(std::move(weights));
}

Weights& Weights::operator-=(const Weights& correction) {
    for (size_t i = 0; i < SIZE; i++) {
        at(i) -= correction[i];
    }

    return *this;
}

Weights& Weights::operator+=(const Weights& correction) {
    for (size_t i = 0; i < SIZE; i++) {
        at(i) += correction[i];
    }

    return *this;
}

Weights& Weights::operator*=(double mult) {
    for (auto& w: *this) {
        w *= mult;
    }

    return *this;
}

double* Weights::startForNeuron(size_t index) {
    return &at(index * Neuron::INPUTS_NUMBER);
}


double Weights::distanceL2(const Weights& correction) const {
    return math::metricsL2(*this, correction);
}

void Weights::saveToFile(const std::string& scheme) {
    std::ofstream fout(fullWeightsName(scheme), std::ios::out);

    for (const auto& w: *this) {
        fout << std::setprecision(9) << w << std::endl;
    }

    fout.close();
}

} // network