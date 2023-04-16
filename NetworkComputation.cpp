#include "NetworkComputation.h"
#include "activation_functions.h"

NetworkComputation::NetworkComputation(const Case& kase, const Weights& weights) :
    case_(kase),
    weights_(weights)
{
    double x = 0;

    for (unsigned wn = 0; wn < Weights::SIZE; wn++) {
        x += getInput(wn) * weights_[wn];
    }

    actual_ = sigmoid(x);
}

Weights NetworkComputation::backPropagation() const {
    Weights correction = Weights::zeroed();

    double target = case_.getTarget();

    for (unsigned wn = 0; wn < Weights::SIZE; ++wn) {
        double contrib = (actual_ - target) * actual_ * (1 - actual_) * getInput(wn);
        correction[wn] += contrib;
    }

    return std::move(correction);
}
