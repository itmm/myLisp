#include "error.h"
#include "string.h"

std::string Error::head() const {
    return "error ";
}

bool Error::is_true() const {
	return false;
}

bool Error::is_equal(Element *other) const {
	if (Element::is_equal(other)) { return true; }

	Error *err = Element::as_error(other);
	return Pair::is_equal_pair(err);
}

Error *Error::as_error() {
	return this;
}

Pair *Error::as_pair() {
	return nullptr;
}
