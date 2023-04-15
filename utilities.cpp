#include "utilities.h"
#include "network.h"

double randomInRange(double min, double max) {
    return min + ((max - min) * rand()) / (RAND_MAX);
}

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
    Weights correction(WEIGHTS_NUM, 0.0);
    int count = 0;

    for (const auto& cs: cases) {
        double target = cs.getTarget();
        double actual = networkComputation(cs, w);

        for (unsigned wn = 0; wn < WEIGHTS_NUM; ++wn) {
            double contrib = (actual - target) * actual * (1 - actual) * (wn + 1 < WEIGHTS_NUM ? cs.getInput(wn) : -1.0);
            correction[wn] += contrib;
        }

        count += 1;
    }

    for (int wn = 0; wn < WEIGHTS_NUM; ++wn) {
        correction[wn] /= count;
    }

    return correction;
}

void updateWeights(Weights& weights, const Weights& correction) {
    assert(weights.size() == WEIGHTS_NUM);
    assert(correction.size() == WEIGHTS_NUM);

    for (int i = 0; i < WEIGHTS_NUM; ++i) {
        weights[i] -= correction[i];
    }
}
