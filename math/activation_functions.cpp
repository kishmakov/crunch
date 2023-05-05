#include <cmath>
#include <map>

#include "activation_functions.h"

namespace math {

static double sigmoidFunciton(double x) {
    double result;
    result = 1 / (1 + exp(-x));
    return result;
}

static double sigmoidDerivative(double x) {
    double ex = exp(-x);
    double denom = (1 + ex);
    return ex / (denom * denom);
}

static double reluFunciton(double x) {
    return x < 0.0 ? 0.0 : x;
}

static double reluDerivative(double x) {
    return x < 0.0 ? 0.0 : 1.0;
}

static std::map<std::string, ActivationFunction> TaggedActivationFunctions = {
        {"sigmoid", {&sigmoidFunciton, &sigmoidDerivative}},
        {"relu", {&reluFunciton, &reluDerivative}}
};

const ActivationFunction& activationByName(const std::string& name) {
    if (!TaggedActivationFunctions.contains(name)) {
        throw std::out_of_range("No activation function named " + name);
    }

    return TaggedActivationFunctions[name];
}

} // math