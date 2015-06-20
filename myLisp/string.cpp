#include "string.h"


bool String::is_true() const {
	return _str.length() > 0;
}

String *String::as_string() { return this; }

void String::to_stream(std::ostream &stream) const {
    stream << "\"" << _str << "\"";
}