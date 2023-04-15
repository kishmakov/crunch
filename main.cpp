#include <cmath>
#include <iomanip>
#include <iostream>

#include "Case.h"
#include "Weights.h"
#include "utilities.h"
#include "NetworkComputation.h"

const unsigned randSeed = 20230402;

int main() {
    std::srand(randSeed);

    auto cases = Case::trainingSet();

    auto weights = Weights::randomlyChosen(-5.0, 5.0);

    for (int trialNumber = 0; trialNumber < 10000; trialNumber++) {
        double result = metricsMSE(cases, weights);

        weights -= correctionMSE(cases, weights);

        std::cout << std::setw(3) << trialNumber << ": ";
        std::cout << std::setw(10) << result << " <-" << weights;

        std::cout << std::endl;
    }

    int score = 0;

    for (const auto& kase: cases) {
        NetworkComputation computation(kase, weights);
        if (std::round(kase.getTarget()) == std::round(computation.getActual())) score++;
    }

    std::cout << score << " out of " << cases.size() << std::endl;

    return 0;
}
