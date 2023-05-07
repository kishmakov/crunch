#ifndef CRUNCH_NETWORK_H
#define CRUNCH_NETWORK_H

#include "math/activation_functions.h"
#include "Neuron.h"
#include "Weights.h"

namespace network {

struct Network {
    const static size_t NEURONS_NUMBER;

    explicit Network(const std::string& packName, Weights weights = Weights());

    [[nodiscard]]
    const Neuron& getNeuron(size_t index) const;

    [[nodiscard]]
    const Weights& getWeights() const { return weights_; }

    void init(Weights weights = Weights());
    void shuffle();
    double react(const std::vector<double>& inputs);

    [[nodiscard]]
    Weights backPropagation(double delta, const std::vector<double>& inputs) const;

    Network& operator+=(const Weights& correction);

private:
    const static double BIAS_INPUT;

    [[nodiscard]]
    std::vector<const double*> getInputPtrs(const std::vector<double>& inputs) const;

    void initNeurons();

    Weights weights_;
    std::vector<Neuron> neurons_;
};

} // network

#endif //CRUNCH_NETWORK_H
