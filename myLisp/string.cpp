#include "string.h"

String *String::as_string() { return this; }

void String::to_stream(std::ostream &stream) const {
    stream << "\"" << _str << "\"";
}