#include "training.h"
#include "utilities.h"

TrainingResult runTraining(const std::vector<Case>& cases,
                           const Weights& initial,
                           uint64_t iterationsNumber,
                           uint64_t snapshotFrequency) {

    TrainingResult tr = {initial };
    tr.history.reserve((iterationsNumber + 1) / snapshotFrequency);

    for (unsigned iteration = 0; iteration < iterationsNumber; ++iteration) {
        if (iteration % snapshotFrequency == 0) tr.takeSnapshot();

        metricsMSE(cases, tr.result);
        tr.result -= correctionMSE(cases, tr.result);
    }

    return std::move(tr);
}
