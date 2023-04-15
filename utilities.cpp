#include "utilities.h"
#include "network.h"


double metricsMSE(const std::vector<Case>& cases, const Weights& w) {
    double SSE = 0;
    int count = 0;

    for (const auto& cs: cases) {
        double actual = networkComputation(cs, w);

        double error = cs.getTarget() - actual;

        SSE += error * error;
        count += 1;
    }

    return SSE / count;
}

Weights correctionMSE(const std::vector<Case>& cases, const Weights& w) {
    Weights correction = Weights::zeroed();

    int count = 0;

    for (const auto& cs: cases) {
        double target = cs.getTarget();
        double actual = networkComputation(cs, w);

        for (unsigned wn = 0; wn < Weights::SIZE; ++wn) {
            double contrib = (actual - target) * actual * (1 - actual) * cs.getInput(wn);
            correction[wn] += contrib;
        }

        count += 1;
    }

    for (int wn = 0; wn < Weights::SIZE; ++wn) {
        correction[wn] /= count;
    }

    return correction;
}

