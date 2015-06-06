#include "fractional.h"

std::ostream &operator<<(std::ostream &output, const Fractional &value) {
    if (!value.denomerator()) {
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
        const auto &denomerator = value.denomerator();
        if (denomerator != 1) {
            output << "/" << denomerator;
        }
    }
    return output;
}