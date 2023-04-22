#ifndef CRUNCH_UTILITIES_H
#define CRUNCH_UTILITIES_H

#include "Case.h"
#include "network/Weights.h"

double metricsL2(const network::Weights& a, const network::Weights& b, unsigned from = 0, unsigned to = network::Weights::SIZE);

double metricsMSE(const std::vector<Case>& cases, const network::Weights& weights);

network::Weights correctionMSE(const std::vector<Case>& cases, const network::Weights& weights);

void saveWeights(const std::string& baseName, const network::Weights& weights);
network::Weights loadWeights(const std::string& baseName);

#endif //CRUNCH_UTILITIES_H
