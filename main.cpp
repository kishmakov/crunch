#include <cmath>
#include <iostream>

#include "Case.h"
#include "math/metrics.h"
#include "network/Network.h"
#include "network/Weights.h"
#include "Plotter.h"
#include "network/Training.h"
#include "utilities.h"

static const unsigned RAND_SEED = 20230402;
static const unsigned REPORTS_NUMBER = 500;
static const unsigned STEPS_PER_REPORT = 1000;

const std::string MODE_TRAIN = "train";
const std::string MODE_CHECK = "check";


void plotWeightsAndMSE(const std::string& baseName, const std::vector<Case>& cases, network::TrainingResult& tr) {
    Plot targetError("-b");
    Plot weightsDistance("-r");

    for (const auto& history: tr.history) {
        network::Network net(tr.packName, history);
        targetError += log10(metricsMSE(cases, net));
        weightsDistance += log10(tr.result.distanceL2(history));
    }

    Plotter plotter("Convergence on Training Set");

    plotter.add("MSE on train set", targetError);
    plotter.add("L_{2} weights", weightsDistance);

    plotter.xlabel = "Iteration / " + std::to_string(STEPS_PER_REPORT);
    plotter.ylabel = "log_{10}";

    plotter.draw(baseName + "_mse_error");
}

// https://github.com/alandefreitas/matplotplusplus/blob/8dbea7d359f7b4f456bca7a6015c32b61ad728f4/source/matplot/util/colors.cpp
void plotNeurons(const std::string& baseName, network::TrainingResult& tr) {
    std::vector<Plot> plots = {
            Plot("-b"),
            Plot("-k"),
            Plot("-c"),
            Plot("-g"),
            Plot("-r")
    };

    network::Network resulting(tr.packName, tr.result);

    for (const auto& history: tr.history) {
        network::Network historic(tr.packName, history);

        for (size_t id = 0; id < network::Network::NEURONS_NUMBER; ++id) {
            auto hist = historic.getNeuron(id).getWeights();
            auto res = resulting.getNeuron(id).getWeights();
            plots[id] += log10(math::metricsL2(hist, res));
        }
    }

    Plotter plotter("Neurons on Training Set");

    for (size_t id = 0; id < network::Network::NEURONS_NUMBER; ++id) {
        plotter.add("Neuron #" + std::to_string(id), plots[id]);
    }

    plotter.xlabel = "Iteration / " + std::to_string(STEPS_PER_REPORT);
    plotter.ylabel = "log_{10} of L_{2}";

    plotter.draw(baseName + "_neurons");
}

void trainNetwork(const std::string& scheme) {
    auto cases = Case::trainingSet();

    auto tr = network::runTraining(cases, REPORTS_NUMBER * STEPS_PER_REPORT, STEPS_PER_REPORT, scheme);

    tr.result.saveToFile(scheme);

    plotWeightsAndMSE(scheme, cases, tr);
    plotNeurons(scheme, tr);
}

void checkNetwork(const std::string& functionName) {
    auto weights = network::Weights::loadFromFile(functionName);

    network::Network network(functionName, weights);

    unsigned score = 0;
    unsigned total = 0;

    for (const auto& kase: Case::trainingSet()) {
        total++;

        double actual = network.react(kase.asInputs());
        if (round(kase.getTarget()) == round(actual)) score++;
        for (unsigned i = 0; i < 4; ++i) {
            std::cout << kase.getInput(i) << " ";
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

    srand(RAND_SEED);

    std::string mode(argv[1]);
    std::string scheme(argv[2]);

    if (mode == MODE_TRAIN) {
        trainNetwork(scheme);
    }

    if (mode == MODE_CHECK) {
        checkNetwork(scheme);
    }

    return 0;
}

