#include <iostream>
#include <bitset>
#include <iomanip>

#include "common.h"
#include "utilites.h"

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

int main() {
    std::srand(randSeed);

    auto cases = trainingCases();

    for (int trialNumber = 0; trialNumber < 100; trialNumber++) {
        Weights weights(WEIGHTS_NUM, 0.0);

        for (int i = 0; i < WEIGHTS_NUM; ++i) {
            weights[i] = randomInRange(-5.0, 5.0);
        }

        double result = metricsMSE(cases, weights);

        std::cout << std::setw(3) << trialNumber << ": ";
        std::cout << std::setw(10) << result;
        std::cout << std::endl;
    }

    return 0;
}
