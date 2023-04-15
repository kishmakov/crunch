#ifndef CRUNCH_CASE_H
#define CRUNCH_CASE_H

#include <cstdint>
#include <vector>

class Case {
    const static uint64_t BITNESS = 2;
    const static uint64_t MASK = ((1 << BITNESS) - 1);

    Case(uint64_t asBits, uint64_t m1, uint64_t m2) {
        bits_ = asBits;
        target_ = double((m1 * m2 >> (BITNESS - 1)) & 1);
    }

public:
    Case(uint64_t asBits) : Case(asBits, MASK & asBits, MASK & (asBits >> BITNESS)) {}
    Case(uint64_t m1, uint64_t m2) : Case((m1 << BITNESS) | m2, m1, m2) {}

    inline double getTarget() const { return target_; }
    inline double getInput(unsigned number) const { return double((bits_ >> number) & 1); }

    static std::vector<Case> trainingSet();

private:
    uint64_t bits_;
    double target_;
};

#endif //CRUNCH_CASE_H
