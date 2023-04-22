#include <fstream>
#include <iomanip>

#include "Weights.h"

namespace network {

const uint64_t Weights::SIZE = 25;

double randomInRange(double min, double max) {
    return min + ((max - min) * rand()) / (RAND_MAX);
}

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

std::ostream& operator<<(std::ostream& os, const Weights& weights) {
    for (const auto& w: weights.weights_) {
        os << std::setprecision(9) << w << std::endl;
    }

    return os;
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

Weights::Weights(std::string fileName) : weights_() {
    std::ifstream fin(fileName);

    double weight;

    while (fin >> weight) {
        weights_.push_back(weight);
    }

    fin.close();
}

} // network