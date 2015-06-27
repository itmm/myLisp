#include "identifier.h"


bool Identifier::is_equal(Element *other) const {
	if (Element::is_equal(other)) { return true; }
	Identifier *otherIdentifier = Element::as_identifier(other);
	return otherIdentifier && otherIdentifier->str() == str();
}

Identifier *Identifier::as_identifier() {
	return this;
}

String *Identifier::as_string() {
	return nullptr;
}

void Identifier::to_stream(std::ostream &stream) const {
	stream << str();
}
