#include "Case.h"

std::vector<Case> Case::trainingSet() {
    std::vector<Case> result;

    for (unsigned n1 = 0; n1 < 4; ++n1) {
        for (unsigned n2 = 0; n2 < 4; ++n2) {
            result.emplace_back(n1, n2);
        }
    }

    return result;
}
