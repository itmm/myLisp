#include "fractional.h"

std::ostream &operator<<(std::ostream &output, const Fractional &value) {
    if (value.isNegative()) {
        output << "-";
    }
    if (!value.denomerator()) {
        if (value.numerator()) {
            output << "Infinity";
        } else {
            output << "NotANumber";
        }
    } else {
        output << value.numerator();
        const auto &denomerator = value.denomerator();
        if (denomerator != 1) {
            output << "/" << denomerator;
        }
    }
    return output;
}