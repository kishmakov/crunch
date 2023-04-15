#ifndef CRUNCH_UTILITIES_H
#define CRUNCH_UTILITIES_H

#include "Case.h"
#include "Weights.h"

double metricsMSE(const std::vector<Case>& cases, const Weights& weights);

Weights correctionMSE(const std::vector<Case>& cases, const Weights& weights);

#endif //CRUNCH_UTILITIES_H
