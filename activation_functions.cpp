#include "activation_functions.h"

#include <math.h>

double sigmoid(double x) {
    double result;
    result = 1 / (1 + exp(-x));
    return result;
}
