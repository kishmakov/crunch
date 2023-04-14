#include "utilities.h"
#include "network.h"

double randomInRange(double min, double max) {
    return min + ((max - min) * rand()) / (RAND_MAX);
}

Inputs caseToInputs(const Case& c) {
    Inputs result = Inputs(4, 0.0);
    result[0] = ((c.first  >> 0) & 1) * 1.0;
    result[1] = ((c.first  >> 1) & 1) * 1.0;
    result[2] = ((c.second >> 0) & 1) * 1.0;
    result[3] = ((c.second >> 1) & 1) * 1.0;
    return result;
}

double getTarget(const std::pair<uint16_t, uint16_t>& cs) {
    uint16_t multiple = cs.first * cs.second;
    return ((multiple >> 1) & 1) * 1.0;
}

double metricsMSE(const std::vector<Case>& cases, const Weights& w) {
    double SSE = 0;
    int count = 0;

    for (const auto& cs: cases) {
        double target = getTarget(cs);
        Inputs inputs = caseToInputs(cs);
        double actual = networkComputation(inputs, w);

        double error = target - actual;

        SSE += error * error;
        count += 1;
    }

    return SSE / count;
}

Weights correctionMSE(const std::vector<Case>& cases, const Weights& w) {
    Weights correction(WEIGHTS_NUM, 0.0);
    int count = 0;

    for (const auto& cs: cases) {
        double target = getTarget(cs);
        Inputs inputs = caseToInputs(cs);
        double actual = networkComputation(inputs, w);

        for (int wn = 0; wn < WEIGHTS_NUM; ++wn) {
            double contrib = (actual - target) * actual * (1 - actual) * (wn + 1 < WEIGHTS_NUM ? inputs[wn] : -1.0);
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
