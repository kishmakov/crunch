#include "NetworkComputation.h"
#include "activation_functions.h"

NetworkComputation::NetworkComputation(const Case& kase, const Weights& weights) :
    case_(kase),
    weights_(weights)
{
    double x = 0;

    for (unsigned wn = 0; wn < Weights::SIZE; wn++) {
        x += getInput(wn) * weights[wn];
    }

    actual_ = sigmoid(x);
}

NetworkComputation NetworkComputation::compute(const Case& kase, const Weights& weights) {
    NetworkComputation computation(kase, weights);
    computation.runBackPropagation();
    return computation;
}

void NetworkComputation::runBackPropagation() {
    double target = case_.getTarget();

    for (unsigned wn = 0; wn < Weights::SIZE; ++wn) {
        double contrib = (actual_ - target) * actual_ * (1 - actual_) * getInput(wn);
        backPropagation_[wn] += contrib;
    }
}
