#include "network/Training.h"

#include <utility>
#include "utilities.h"

namespace network {

Training::Training(std::string scheme, const size_t stepsPerReport) :
    net(scheme),
    scheme(std::move(scheme)),
    stepsPerReport(stepsPerReport)
{}

void Training::init(const std::vector<Case>& cases, size_t candidatesNumber) {
    std::vector<network::Weights> startingCandidates;
    double minError = 1e10;
    size_t minId = -1;

    for (size_t currentId = 0; currentId < candidatesNumber; ++currentId) {
        net.shuffle();
        startingCandidates.push_back(net.getWeights());
        double currentError = metricsMSE(cases, net);

        if (currentError < minError) {
            minError = currentError;
            minId = currentId;
        }
    }

    net.init(startingCandidates[minId]);
}

void Training::run(const std::vector<Case>& cases, size_t stepsTotal) {
    history.reserve((stepsTotal + 1) / stepsPerReport);

    for (unsigned iteration = 0; iteration < stepsTotal; ++iteration) {
        if (iteration % stepsPerReport == 0) {
            history.push_back(net.getWeights());
        }

        correctionMSE(cases, net);
    }

    result = net.getWeights();
}

} // network