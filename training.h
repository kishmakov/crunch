#ifndef CRUNCH_TRAINING_H
#define CRUNCH_TRAINING_H

#include <string>

#include "network/Weights.h"
#include "Case.h"

typedef std::vector<network::Weights> WeightsHistory;

struct TrainingResult {
    network::Weights result;
    WeightsHistory history;
    std::string functionName;

    inline void takeSnapshot() { history.push_back(result); }
};

[[maybe_unused]] TrainingResult
runTraining(const std::vector<Case>& cases,
            const network::Weights& initial,
            uint64_t iterationsNumber,
            uint64_t snapshotFrequency,
            const std::string& functionName);

#endif //CRUNCH_TRAINING_H
