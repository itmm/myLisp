#include "string.h"

String *String::to_string() { return this; }

void String::to_stream(std::ostream &stream) {
    stream << "\"" << _str << "\"";
}