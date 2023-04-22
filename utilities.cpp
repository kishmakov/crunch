#include <cmath>
#include <fstream>
#include <string>

#include "NetworkComputation.h"
#include "utilities.h"

double metricsL2(const Weights& a, const Weights& b, unsigned int from, unsigned int to) {
    assert(to > from);

    double SSE = 0;

    for (unsigned i = from; i < to; ++i) {
        double diff = a[i] - b[i];
        SSE += diff * diff;
    }

    SSE /= to - from;

    return std::sqrt(SSE);
}

double metricsMSE(const std::vector<Case>& cases, const Weights& weights) {
    double SSE = 0;

    for (const auto& kase: cases) {
        double error = kase.getTarget() - NetworkComputation(kase, weights).getActual();
        SSE += error * error;
    }

    return SSE / double(cases.size());
}

Weights correctionMSE(const std::vector<Case>& cases, const Weights& weights) {
    Weights correction = Weights::zeroed();

    for (const auto& kase: cases) {
        auto computation = NetworkComputation(kase, weights);
        correction += computation.backPropagation();
    }

    correction *= 1.0 / double(cases.size());
    return correction;
}

[[maybe_unused]] inline std::string fullWeightsName(const std::string& base) { return base + ".txt"; }

void saveWeights(const std::string& baseName, const Weights& weights) {
    std::ofstream fout(fullWeightsName(baseName), std::ios::out);
    fout << weights;
}

Weights loadWeights(const std::string& baseName) {
    return Weights(fullWeightsName(baseName));
}