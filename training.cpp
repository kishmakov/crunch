#include "training.h"
#include "utilities.h"

TrainingResult runTraining(const std::vector<Case>& cases,
                           uint64_t iterationsNumber,
                           uint64_t snapshotFrequency,
                           const std::string& packName) {
    network::Network net(packName);

    TrainingResult tr = {network::Weights::zeroed()};
    tr.packName = packName;
    tr.history.reserve((iterationsNumber + 1) / snapshotFrequency);

    for (unsigned iteration = 0; iteration < iterationsNumber; ++iteration) {
        if (iteration % snapshotFrequency == 0) tr.takeSnapshot(net);
        correctionMSE(cases, net, packName);
    }

    tr.result = net.getWeights();

    return std::move(tr);
}
