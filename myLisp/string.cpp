#include "string.h"

bool String::is_true() const {
	return _str.length() > 0;
}

bool String::is_equal(Element *other) const {
	if (Element::is_equal(other)) { return true; }
	String *otherString = Element::as_string(other);
	return otherString && otherString->str() == _str;
}


bool String::is_less(Element *other) const {
    String *value = Element::as_string(other);
    return value && _str < value->str();
}

String *String::as_string() { return this; }

void String::to_stream(std::ostream &stream) const {
    stream << _str;
}