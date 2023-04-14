#include "utilites.h"
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

