#ifndef CRUNCH_UTILITIES_H
#define CRUNCH_UTILITIES_H

#include "Case.h"
#include "network/Weights.h"
#include "network/Network.h"

double metricsMSE(const std::vector<Case>& cases, network::Network& net);

network::Weights
correctionMSE(const std::vector<Case>& cases, const network::Weights& weights, const std::string& activationFunction);

#endif //CRUNCH_UTILITIES_H
