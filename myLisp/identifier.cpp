#include "identifier.h"

Identifier *Identifier::as_identifier() {
	return this;
}

String *Identifier::as_string() {
	return nullptr;
}

void Identifier::to_stream(std::ostream &stream) const {
	stream << str();
}
