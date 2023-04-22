#include <cmath>
#include <fstream>
#include <string>

#include "network/NetworkComputation.h"
#include "utilities.h"

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

double metricsMSE(const std::vector<Case>& cases, const network::Weights& weights) {
    double SSE = 0;

    for (const auto& kase: cases) {
        double error = kase.getTarget() - network::NetworkComputation(kase, weights).getActual();
        SSE += error * error;
    }

    return SSE / double(cases.size());
}

network::Weights correctionMSE(const std::vector<Case>& cases, const network::Weights& weights) {
    network::Weights correction = network::Weights::zeroed();

    for (const auto& kase: cases) {
        auto computation = network::NetworkComputation(kase, weights);
        correction += computation.backPropagation();
    }

    correction *= 1.0 / double(cases.size());
    return correction;
}