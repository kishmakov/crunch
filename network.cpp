#include "network.h"
#include "activation_functions.h"

double networkComputation(const Case& kase, const Weights& weights) {
    double x = 0;

    for (unsigned i = 0; i < 4; i++) {
        x += kase.getInput(i) * weights[i];
    }

    return sigmoid(x - weights.bias());
}
