#ifndef CRUNCH_WEIGHTS_H
#define CRUNCH_WEIGHTS_H

#include <vector>

namespace network {

class Weights {
    explicit Weights(std::vector<double>&& weights) : weights_(std::move(weights)) {}

public:
    const static uint64_t SIZE;

    static Weights randomlyChosen(double min, double max);
    static Weights zeroed();
    static Weights loadFromFile(const std::string& baseName);

    Weights& operator-=(const Weights& correction);
    Weights& operator+=(const Weights& correction);
    Weights& operator*=(double mult);
    double& operator[](unsigned index);
    const double& operator[](unsigned index) const;
    double distanceL2(const Weights& correction) const;

    void saveToFile(const std::string& baseName);

private:
    friend class Network;
    std::vector<double> weights_;
};

} // network

#endif //CRUNCH_WEIGHTS_H
