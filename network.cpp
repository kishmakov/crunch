#include "network.h"
#include "activation_functions.h"

double networkComputation(const Inputs& inputs, const Weights& weights) {
    assert(inputs.size() == 4);
    assert(weights.size() == WEIGHTS_NUM);

    double x = 0;

    for (int i = 0; i < 4; i++) {
        x += inputs[i] * weights[i];
    }

    return sigmoid(x - weights[WEIGHTS_NUM - 1]);
}
