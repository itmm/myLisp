#include "fractional.h"

std::ostream &operator<<(std::ostream &output, const Fractional &value) {
    if (!value.denominator()) {
        if (value.isNegative()) {
            output << "(- ";
        }
        if (value.numerator()) {
            output << "Infinity";
        } else {
            output << "NotANumber";
        }
        if (value.isNegative()) {
            output << ")";
        }
    } else {
        if (value.isNegative()) {
            output << "-";
        }
        output << value.numerator();
        const auto &denominator = value.denominator();
        if (denominator != 1) {
            output << "/" << denominator;
        }
    }
    return output;
}