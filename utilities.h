#ifndef CRUNCH_UTILITIES_H
#define CRUNCH_UTILITIES_H

#include "Case.h"
#include "Weights.h"

double metricsMSE(const std::vector<Case>& cases, const Weights& w);

Weights correctionMSE(const std::vector<Case>& cases, const Weights& w);

#endif //CRUNCH_UTILITIES_H
