#include "fractional.h"

std::ostream &operator<<(std::ostream &output, const Fractional &value) {
    if (!value.denominator()) {
        if (value.isNegative()) {
            output << "(- ";
        }
        if (value.numerator()) {
            output << "infinity";
        } else {
            output << "not-a-number";
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
        if (!(denominator == BigInt(1))) {
            output << "/" << denominator;
        }
    }
    return output;
}