#include "error.h"
#include "string.h"

bool Error::is_true() const {
	return false;
}

bool Error::is_equal(Element *other) const {
	if (Element::is_equal(other)) { return true; }

	Error *err = Element::as_error(other);
	return err && str() == err->str();
}

Error *Error::as_error() {
	return this;
}

String *Error::as_string() {
	return nullptr;
}

void Error::to_stream(std::ostream &stream) const {
	stream << "(error \"" << str() << "\")";
}
