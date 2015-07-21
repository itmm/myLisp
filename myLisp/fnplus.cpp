#include "fnplus.h"

#include "number.h"
#include "pair.h"


Ptr FunctionPlus::empty_case(State &callerState) {
	return callerState.creator()->new_number(BigInt(0));
}

Ptr FunctionPlus::setup(State &callerState, bool &stop) {
	return callerState.creator()->new_number(BigInt(0));
}

Ptr FunctionPlus::argument(Ptr intermediate, Element *element, State &callerState, bool &stop) {
	Number *sum = Element::as_number(intermediate);
	Number *value = Element::as_number(element);
	if (!sum || !value) return callerState.creator()->new_error("+ expects numeric arguments");
	return callerState.creator()->new_number(sum->value() + value->value());
}
