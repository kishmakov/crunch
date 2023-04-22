#ifndef CRUNCH_UTILITIES_H
#define CRUNCH_UTILITIES_H

#include "Case.h"
#include "Weights.h"

double metricsL2(const Weights& a, const Weights& b, unsigned from = 0, unsigned to = Weights::SIZE);

double metricsMSE(const std::vector<Case>& cases, const Weights& weights);

Weights correctionMSE(const std::vector<Case>& cases, const Weights& weights);

void saveWeights(const std::string& baseName, const Weights& weights);
Weights loadWeights(const std::string& baseName);

#endif //CRUNCH_UTILITIES_H
