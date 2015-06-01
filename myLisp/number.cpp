#include "number.h"

Number *Number::as_number() { return this; }

void Number::to_stream(std::ostream &output) {
    output << _value;
}
