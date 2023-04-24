#include "utilities.h"
#include "network/Network.h"


double metricsMSE(const std::vector<Case>& cases, network::Network& net) {
    double SSE = 0;

    for (const auto& kase: cases) {
        double error = kase.getTarget() - net.react(kase.asInputs());
        SSE += error * error;
    }

    return SSE / double(cases.size());
}

network::Weights
correctionMSE(const std::vector<Case>& cases, const network::Weights& weights, const std::string& activationFunction) {
    network::Weights correctionN = network::Weights::zeroed();

    for (const auto& kase: cases) {
        network::Network net(weights,activationFunction);
        auto inputs = kase.asInputs();
        double actual = net.react(inputs);
        auto newC = net.backPropagation(actual - kase.getTarget(), inputs);
        correctionN += newC;
    }

    correctionN *= 1.0 / double(cases.size());

    return correctionN;
}