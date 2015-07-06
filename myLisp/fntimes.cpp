#include "fntimes.h"

#include "number.h"

Ptr FunctionTimes::empty_case(State &callerState) {
	return callerState.creator()->new_number(1);
}

Ptr FunctionTimes::setup(State &callerState, bool &stop) {
	return callerState.creator()->new_number(1);
}

Ptr FunctionTimes::argument(Ptr intermediate, Element *element, State &callerState, bool &stop) {
	Number *product = Element::as_number(intermediate);
	Number *value = Element::as_number(element);
	if (!product || !value) return callerState.creator()->new_error("* expects numeric arguments");
	return callerState.creator()->new_number(product->value() * value->value());
}
