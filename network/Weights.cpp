#include <fstream>
#include <iomanip>

#include "math/metrics.h"
#include "Neuron.h"
#include "Weights.h"

namespace network {

const size_t Weights::SIZE = 25;


[[maybe_unused]] inline std::string fullWeightsName(const std::string& base) { return base + ".txt"; }

//Weights Weights::randomlyChosen(double min, double max) {
//    std::vector<double> weights(SIZE, 0.0);
//
//    for (size_t i = 0; i < SIZE; ++i) {
//        weights[i] = randomInRange(min, max);
//    }
//
//    return Weights(std::move(weights));
//}

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
        weights_[i] -= correction.weights_[i];
    }

    return *this;
}

Weights& Weights::operator+=(const Weights& correction) {
    for (size_t i = 0; i < SIZE; i++) {
        weights_[i] += correction.weights_[i];
    }

    return *this;
}

Weights& Weights::operator*=(double mult) {
    for (auto& w: weights_) {
        w *= mult;
    }

    return *this;
}

double& Weights::operator[](size_t index) {
    if (index >= SIZE) {
        throw std::out_of_range("Index out of range");
    }

    return weights_[index];
}

const double& Weights::operator[](size_t index) const {
    if (index >= SIZE) {
        throw std::out_of_range("Index out of range");
    }

    return weights_[index];
}

double* Weights::startForNeuron(size_t index) {
    return &weights_[index * Neuron::INPUTS_NUMBER];
}


double Weights::distanceL2(const Weights& correction) const {
    return math::metricsL2(weights_, correction.weights_);
}

void Weights::saveToFile(const std::string& baseName) {
    std::ofstream fout(fullWeightsName(baseName), std::ios::out);

    for (const auto& w: weights_) {
        fout << std::setprecision(9) << w << std::endl;
    }

    fout.close();
}

} // network