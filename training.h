#ifndef CRUNCH_TRAINING_H
#define CRUNCH_TRAINING_H

#include <string>

#include "Case.h"
#include "network/Network.h"
#include "network/Weights.h"

typedef std::vector<network::Weights> WeightsHistory;

struct TrainingResult {
    network::Weights result;
    WeightsHistory history;
    std::string packName;

    inline void takeSnapshot(const network::Network& net) { history.push_back(net.getWeights()); }
};

[[maybe_unused]] TrainingResult
runTraining(const std::vector<Case>& cases,
            uint64_t iterationsNumber,
            uint64_t snapshotFrequency,
            const std::string& packName);

#endif //CRUNCH_TRAINING_H
