#include <cmath>

#include "activation_functions.h"

namespace network {

double sigmoid(double x) {
    double result;
    result = 1 / (1 + exp(-x));
    return result;
}

} // network