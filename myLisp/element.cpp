#include "element.h"

Element::~Element() {}

Dictionary *Element::as_dictionary() { return nullptr; }
Function *Element::as_function() { return nullptr; }
Number *Element::as_number() { return nullptr; }
Pair *Element::as_pair() { return nullptr; }
String *Element::as_string() { return nullptr; }

Dictionary *Element::as_dictionary(Element *elm) {
	return elm ? elm->as_dictionary() : static_cast<Dictionary *>(nullptr);
}

Function *Element::as_function(Element *elm) {
	return elm ? elm->as_function() : static_cast<Function *>(nullptr);
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
