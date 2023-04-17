#ifndef CRUNCH_TRAINING_H
#define CRUNCH_TRAINING_H

#include "Weights.h"
#include "Case.h"

typedef std::vector<Weights> WeightsHistory;

struct TrainingResult {
    Weights result;
    WeightsHistory history;

    inline void takeSnapshot() { history.push_back(result); }
};

[[maybe_unused]] TrainingResult runTraining(
        const std::vector<Case>& cases,
        const Weights& initial,
        uint64_t iterationsNumber,
        uint64_t snapshotFrequency);

#endif //CRUNCH_TRAINING_H
