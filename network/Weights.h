#ifndef CRUNCH_WEIGHTS_H
#define CRUNCH_WEIGHTS_H

#include <vector>

namespace network {

class Weights {
    explicit Weights(std::vector<double>&& weights) : weights_(std::move(weights)) {}

public:
    const static size_t SIZE;

    static Weights zeroed();
    static Weights loadFromFile(const std::string& baseName);

    Weights& operator-=(const Weights& correction);
    Weights& operator+=(const Weights& correction);
    Weights& operator*=(double mult);
    double& operator[](size_t index);
    const double& operator[](size_t index) const;

    double* startForNeuron(size_t index);
    double distanceL2(const Weights& correction) const;

    void saveToFile(const std::string& scheme);

private:
    friend class Network;
    std::vector<double> weights_;
};

} // network

#endif //CRUNCH_WEIGHTS_H
