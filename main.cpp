#include <iostream>
#include <bitset>
#include <iomanip>

#include "common.h"
#include "utilities.h"

const unsigned randSeed = 20230402;

std::vector<Case> trainingCases() {
    std::vector<Case> result(0);

    for (uint16_t n1 = 0; n1 < 4; ++n1) {
        for (uint16_t n2 = 0; n2 < 4; ++n2) {
            result.emplace_back(n1, n2);
        }
    }

    return result;
}

Weights initialWeights() {
    Weights weights(WEIGHTS_NUM, 0.0);

    for (int i = 0; i < WEIGHTS_NUM; ++i) {
        weights[i] = randomInRange(-5.0, 5.0);
    }

    return weights;
}

int main() {
    std::srand(randSeed);

    auto cases = trainingCases();

    auto weights = initialWeights();

    for (int trialNumber = 0; trialNumber < 10000; trialNumber++) {
        double result = metricsMSE(cases, weights);

        auto correction = correctionMSE(cases, weights);
        updateWeights(weights, correction);

        std::cout << std::setw(3) << trialNumber << ": ";
        std::cout << std::setw(10) << result << " <-";

        for (const auto& w: weights) {
            std::cout << std::setw(10) << w;
        }

        std::cout << std::endl;
    }

    return 0;
}
