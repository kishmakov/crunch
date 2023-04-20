#include <cmath>
#include <iostream>

#include <matplot/matplot.h>

#include "Case.h"
#include "NetworkComputation.h"
#include "training.h"
#include "utilities.h"
#include "Weights.h"

const unsigned RAND_SEED = 20230402;

const std::string MODE_TRAIN = "train";
const std::string MODE_CHECK = "check";

void trainNetwork(const std::string& baseName, unsigned randSeed) {
    srand(randSeed);

    auto weights = Weights::randomlyChosen(-5.0, 5.0);

    auto cases = Case::trainingSet();

    auto tr = runTraining(cases, weights, 500000, 1000);

    saveWeights(baseName, tr.result);

    std::vector<double> iterations;
    std::vector<double> metrics;
    std::vector<double> coeffDiffs;

    double lastCF = tr.history.back()[0];

    iterations.reserve(tr.history.size());
    metrics.reserve(tr.history.size());
    coeffDiffs.reserve(tr.history.size());


    double step = 1.0;
    double log10inv = 1.0 / log(10.0);
    double x = 0.0;

    for (const auto& weights: tr.history) {
        iterations.push_back(x);
        x += step;

        metrics.push_back(log(metricsMSE(cases, weights)) * log10inv);
        coeffDiffs.push_back(weights[0] - lastCF);
    }

    matplot::plot(iterations, metrics, "-");
    matplot::save(baseName + "_metrics.svg");

    matplot::cla();

    matplot::plot(iterations, coeffDiffs, "-");
    matplot::save(baseName + "_coefficients.svg");
}

void checkNetwork(const std::string& baseName) {
    Weights weights = loadWeights(baseName);

    auto cases = Case::trainingSet();

    int score = 0;

    for (const auto& kase: cases) {
        NetworkComputation computation(kase, weights);
        if (round(kase.getTarget()) == round(computation.getActual())) score++;
        for (unsigned i = 0; i < 4; ++i) {
            std::cout << i << "=" << kase.getInput(i) << " ";
        }
        std::cout << ": t=" << kase.getTarget();
        std::cout << " a=" << computation.getActual();
        std::cout << std::endl;
    }

    std::cout << score << " out of " << cases.size() << std::endl;
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error: not enough arguments." << std::endl;
        std::cerr << "Usage: crunch <mode> <file name>" << std::endl;
        return 1;
    }

    std::string mode(argv[1]);
    std::string fileName(argv[2]);

    if (mode == MODE_TRAIN) {
        trainNetwork(fileName, RAND_SEED);
    }

    if (mode == MODE_CHECK) {
        checkNetwork(fileName);
    }

    return 0;
}

