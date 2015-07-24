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

void String::to_stream(std::ostream &stream, bool escape) const {
	if (escape) {
		stream << '"';
		auto cur = _str.begin();
		auto end = _str.end();
		for(; cur != end; ++cur) {
			if (*cur == '\\' || *cur == '"') stream << '\\';
			stream << *cur;
		}
		stream << '"';
	} else {
    	stream << _str;
	}
}