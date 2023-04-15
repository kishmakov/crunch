#include "network.h"
#include "activation_functions.h"

double networkComputation(const Case& kase, const Weights& weights) {
    assert(weights.size() == WEIGHTS_NUM);

    double x = 0;

    for (unsigned i = 0; i < 4; i++) {
        x += kase.getInput(i) * weights[i];
    }

    return sigmoid(x - weights[WEIGHTS_NUM - 1]);
}
