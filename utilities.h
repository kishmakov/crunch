#ifndef CRUNCH_UTILITIES_H
#define CRUNCH_UTILITIES_H

#include "Case.h"
#include "common.h"

double randomInRange(double min, double max);

double metricsMSE(const std::vector<Case>& cases, const Weights& w);

Weights correctionMSE(const std::vector<Case>& cases, const Weights& w);

void updateWeights(Weights& weights, const Weights& correction);

#endif //CRUNCH_UTILITIES_H
