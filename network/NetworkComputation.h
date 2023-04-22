#ifndef CRUNCH_NETWORKCOMPUTATION_H
#define CRUNCH_NETWORKCOMPUTATION_H

#include "../Case.h"
#include "Weights.h"

namespace network {

class NetworkComputation {
public:
    NetworkComputation(const Case& kase, const Weights& weights);

    [[nodiscard]] double getActual(unsigned id = 4) const;
    [[nodiscard]] Weights backPropagation() const;

private:
    const Case& case_;
    const Weights& weights_;

    std::vector<double> actual_ = std::vector<double>(5, 0.0);

    [[nodiscard]] inline double getInput(unsigned index) const {
        if (index >= 20) {
            index -= 20;
            return index < 4 ? actual_[index] : -1.0;
        }

        index %= 5;
        return index < 4 ? case_.getInput(index) : -1.0;
    }
};

} // network

#endif //CRUNCH_NETWORKCOMPUTATION_H
