#include <fstream>
#include <iomanip>

#include "Weights.h"

namespace network {

const uint64_t Weights::SIZE = 25;

double randomInRange(double min, double max) {
    return min + ((max - min) * rand()) / (RAND_MAX);
}

[[maybe_unused]] inline std::string fullWeightsName(const std::string& base) { return base + ".txt"; }

Weights Weights::randomlyChosen(double min, double max) {
    std::vector<double> weights(SIZE, 0.0);

    for (unsigned i = 0; i < SIZE; ++i) {
        weights[i] = randomInRange(min, max);
    }

    return Weights(std::move(weights));
}

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
    for (unsigned i = 0; i < SIZE; i++) {
        weights_[i] -= correction.weights_[i];
    }

    return *this;
}

Weights& Weights::operator+=(const Weights& correction) {
    for (unsigned i = 0; i < SIZE; i++) {
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

double& Weights::operator[](unsigned index) {
    if (index >= SIZE) {
        throw std::out_of_range("Index out of range");
    }

    return weights_[index];
}

const double& Weights::operator[](unsigned index) const {
    if (index >= SIZE) {
        throw std::out_of_range("Index out of range");
    }

    return weights_[index];
}

void Weights::saveToFile(const std::string& baseName) {
    std::ofstream fout(fullWeightsName(baseName), std::ios::out);

    for (const auto& w: weights_) {
        fout << std::setprecision(9) << w << std::endl;
    }

    fout.close();
}

} // network