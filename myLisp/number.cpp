#include "number.h"

Number *Number::as_number() { return this; }

void Number::to_stream(std::ostream &output, bool) const {
    output << _value;
}

bool Number::is_true() const {
	return _value.numerator() != BigInt(0);
}

bool Number::is_equal(Element *other) const {
	if (Element::is_equal(other)) { return true; }
	Number *otherNum = Element::as_number(other);
	return otherNum && otherNum->value() == _value;
}

bool Number::is_less(Element *other) const {
	Number *otherValue = Element::as_number(other);
	if (!otherValue) { return false; }
	return _value < otherValue->value();
}
