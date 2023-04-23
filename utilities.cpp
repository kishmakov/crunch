#include <cmath>

#include "utilities.h"
#include "network/Network.h"

double metricsL2(const network::Weights& a, const network::Weights& b, unsigned int from, unsigned int to) {
    assert(to > from);

    double SSE = 0;

    for (unsigned i = from; i < to; ++i) {
        double diff = a[i] - b[i];
        SSE += diff * diff;
    }

    SSE /= to - from;

    return std::sqrt(SSE);
}

double metricsL2(const std::vector<double>& a, const std::vector<double>& b) {
    assert(a.size() == b.size());

    double SSE = 0;

    for (size_t i = 0; i < a.size(); ++i) {
        double diff = a[i] - b[i];
        SSE += diff * diff;
    }

    SSE /= a.size();

    return std::sqrt(SSE);
}

double metricsMSE(const std::vector<Case>& cases, network::Network& net) {
    double SSE = 0;

    for (const auto& kase: cases) {
        double error = kase.getTarget() - net.react(kase.asInputs());
        SSE += error * error;
    }

    return SSE / double(cases.size());
}

network::Weights correctionMSE(const std::vector<Case>& cases, const network::Weights& weights) {
    network::Weights correctionN = network::Weights::zeroed();

    for (const auto& kase: cases) {
        network::Network net(weights);
        auto inputs = kase.asInputs();
        double actual = net.react(inputs);
        auto newC = net.backPropagation(actual - kase.getTarget(), inputs);
        correctionN += newC;
    }

    correctionN *= 1.0 / double(cases.size());

    return correctionN;
}