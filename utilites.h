#ifndef CRUNCH_UTILITES_H
#define CRUNCH_UTILITES_H

#include "common.h"

double randomInRange(double min, double max);

Inputs caseToInputs(const Case& c);

double metricsMSE(const std::vector<Case>& cases, const Weights& w);

#endif //CRUNCH_UTILITES_H
