#include "network/Training.h"
#include "utilities.h"

namespace network {

const size_t CANDIDATES_NUMBER = 16;

TrainingResult runTraining(const std::vector<Case>& cases,
                           uint64_t iterationsNumber,
                           uint64_t snapshotFrequency,
                           const std::string& packName) {
    network::Network net(packName);

    std::vector<network::Weights> startingCandidates;
    double minError = 1e10;
    size_t minId = -1;

    for (size_t currentId = 0; currentId < CANDIDATES_NUMBER; ++currentId) {
        net.init();
        startingCandidates.push_back(net.getWeights());
        double currentError = metricsMSE(cases, net);

        if (currentError < minError) {
            minError = currentError;
            minId = currentId;
        }
    }

    net = network::Network(packName, startingCandidates[minId]);

    TrainingResult tr;
    tr.packName = packName;
    tr.history.reserve((iterationsNumber + 1) / snapshotFrequency);

    for (unsigned iteration = 0; iteration < iterationsNumber; ++iteration) {
        if (iteration % snapshotFrequency == 0) tr.takeSnapshot(net);
        correctionMSE(cases, net, packName);
    }

    tr.result = net.getWeights();

    return std::move(tr);
}

Training::Training(const std::string& scheme, size_t stepsPerReport) :
    scheme(scheme),
    stepsPerReport(stepsPerReport)
{

}
} // network