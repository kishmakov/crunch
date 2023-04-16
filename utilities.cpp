#include "utilities.h"
#include "NetworkComputation.h"


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

