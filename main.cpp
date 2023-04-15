#include <cmath>
#include <iomanip>
#include <iostream>

#include "Case.h"
#include "common.h"
#include "utilities.h"
#include "network.h"

const unsigned randSeed = 20230402;

Weights initialWeights() {
    Weights weights(WEIGHTS_NUM, 0.0);

    for (int i = 0; i < WEIGHTS_NUM; ++i) {
        weights[i] = randomInRange(-5.0, 5.0);
    }

    return weights;
}

int main() {
    std::srand(randSeed);

    auto cases = Case::trainingSet();

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

    int score = 0;

    for (const auto& cs: cases) {
        double actual = networkComputation(cs, weights);

        if (std::round(cs.getTarget()) == std::round(actual)) score++;
    }

    std::cout << score << " out of " << cases.size() << std::endl;

    return 0;
}
