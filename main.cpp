#include <cmath>
#include <iostream>

#include "Case.h"
#include "network/Network.h"
#include "network/Weights.h"
#include "Plotter.h"
#include "training.h"
#include "utilities.h"

static const unsigned RAND_SEED = 20230402;
static const unsigned REPORTS_NUMBER = 500;
static const unsigned STEPS_PER_REPORT = 1000;

const std::string MODE_TRAIN = "train";
const std::string MODE_CHECK = "check";


void trainNetwork(const std::string& baseName, unsigned randSeed) {
    srand(randSeed);

    auto weights = network::Weights::randomlyChosen(-5.0, 5.0);

    auto cases = Case::trainingSet();

    auto tr = runTraining(cases, weights, REPORTS_NUMBER * STEPS_PER_REPORT, STEPS_PER_REPORT);

    tr.result.saveToFile(baseName);

    Plot targetError("-b");
    Plot weightsDistance("-r");

    for (const auto& history: tr.history) {
        targetError += log10(metricsMSE(cases, history));
        weightsDistance += log10(metricsL2(history, tr.result));
    }

    Plotter plotter("Convergence on Training Set");

    plotter.add("MSE on train set", targetError);
    plotter.add("L_{2} weights", weightsDistance);

    plotter.xlabel = "Iteration / " + std::to_string(STEPS_PER_REPORT);
    plotter.ylabel = "log_{10}";

    plotter.draw(baseName + "_mse_error");
}

void checkNetwork(const std::string& baseName) {
    auto weights = network::Weights::loadFromFile(baseName);

    network::Network network(weights);

    unsigned score = 0;
    unsigned total = 0;

    for (const auto& kase: Case::trainingSet()) {
        total++;

        double actual = network.react(kase.asInputs());
        if (round(kase.getTarget()) == round(actual)) score++;
        for (unsigned i = 0; i < 4; ++i) {
            std::cout << i << "=" << kase.getInput(i) << " ";
        }
        std::cout << ": t=" << kase.getTarget();
        std::cout << " a=" << actual;
        std::cout << std::endl;
    }

    std::cout << score << " out of " << total << std::endl;
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

