#include "element.h"
#include "dictionary.h"

void Element::add_to_visit(Collector::Visitor &visitor) {}

Element::~Element() {}

bool Element::is_true() const { return false; }
Dictionary *Element::as_dictionary() { return nullptr; }
Error *Element::as_error() { return nullptr; }
Function *Element::as_function() { return nullptr; }
Identifier *Element::as_identifier() { return nullptr; }
Number *Element::as_number() { return nullptr; }
Pair *Element::as_pair() { return nullptr; }
String *Element::as_string() { return nullptr; }

bool Element::is_true(Element *elm) {
	return elm ? elm->is_true() : false;
}

bool Element::is_equal(Element *other) const {
	return this == other;
}

Dictionary *Element::as_dictionary(Element *elm) {
	return elm ? elm->as_dictionary() : static_cast<Dictionary *>(nullptr);
}

Error *Element::as_error(Element *elm) {
	return elm ? elm->as_error() : static_cast<Error *>(nullptr);
}

Function *Element::as_function(Element *elm) {
	return elm ? elm->as_function() : static_cast<Function *>(nullptr);
}

Identifier *Element::as_identifier(Element *elm) {
	return elm ? elm->as_identifier() : static_cast<Identifier *>(nullptr);
}

Number *Element::as_number(Element *elm) {
	return elm ? elm ->as_number() : static_cast<Number *>(nullptr);
}

Pair *Element::as_pair(Element *elm) {
	return elm ? elm->as_pair() : static_cast<Pair *>(nullptr);
}

String *Element::as_string(Element *elm) {
	return elm ? elm->as_string() : static_cast<String *>(nullptr);
}
