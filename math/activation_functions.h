#ifndef CRUNCH_ACTIVATION_FUNCTIONS_H
#define CRUNCH_ACTIVATION_FUNCTIONS_H

#include <string>

namespace math {

typedef double (*DoubleFunction)(double);

struct ActivationFunction {
    DoubleFunction function;
    DoubleFunction derivative;
};

const ActivationFunction& activationByName(const std::string& name);

} // math

#endif //CRUNCH_ACTIVATION_FUNCTIONS_H

