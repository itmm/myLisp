#include "number.h"

Number *Number::as_number() { return this; }

void Number::to_stream(std::ostream &output) const {
    output << _value;
}

bool Number::is_true() const {
	return _value.numerator() != 0;
}
