#ifndef CRUNCH_WEIGHTS_H
#define CRUNCH_WEIGHTS_H

#include <vector>

namespace network {

struct Weights : std::vector<double> {
    Weights() : std::vector<double>(SIZE, 0.0) {}
    explicit Weights(std::vector<double>&& weights) : std::vector<double>(std::move(weights)) {}

    const static size_t SIZE;

    static Weights loadFromFile(const std::string& baseName);

    Weights& operator-=(const Weights& correction);
    Weights& operator+=(const Weights& correction);
    Weights& operator*=(double mult);

    double* startForNeuron(size_t index);
    double distanceL2(const Weights& correction) const;

    void saveToFile(const std::string& scheme);
};

} // network

#endif //CRUNCH_WEIGHTS_H
