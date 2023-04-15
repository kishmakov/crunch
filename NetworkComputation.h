#ifndef CRUNCH_NETWORKCOMPUTATION_H
#define CRUNCH_NETWORKCOMPUTATION_H

#include "Case.h"
#include "Weights.h"

class NetworkComputation {
public:
    NetworkComputation(const Case& kase, const Weights& weights);

    static NetworkComputation compute(const Case& kase, const Weights& weights);

    [[nodiscard]] inline double getActual() const { return actual_; }
    [[nodiscard]] inline const Weights& backPropagation() const { return backPropagation_; }

private:
    const Case& case_;
    const Weights& weights_;

    double actual_;
    Weights backPropagation_ = Weights::zeroed();

    void runBackPropagation();

    [[nodiscard]] inline double getInput(unsigned index) const {
        return index < 4 ? case_.getInput(index) : -1.0;
    }
};

#endif //CRUNCH_NETWORKCOMPUTATION_H
