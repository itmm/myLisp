#include "function.h"

Function *Function::as_function() {
	return this;
}

void Function::to_stream(std::ostream &stream) const {
	stream << "[#FUNCTION#]";
}

Element* Function::apply(Element *arguments) {
	return arguments;
}
