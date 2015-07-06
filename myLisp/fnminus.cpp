#include "fnminus.h"

#include "number.h"

Ptr FunctionMinus::empty_case(State &callerState) {
	return callerState.creator()->new_number(-Fractional(1));
}

Ptr FunctionMinus::first_argument(Ptr intermediate, Element *element, bool hasMore, State &callerState, bool &stop) {
	Number *value = Element::as_number(element);
	if (!value) return callerState.creator()->new_error("- expects numeric arguments");
	return hasMore ? Ptr(value, callerState.collector()) : callerState.creator()->new_number(-value->value());
}

Ptr FunctionMinus::argument(Ptr intermediate, Element *element, State &callerState, bool &stop) {
	Number *difference = Element::as_number(intermediate);
	Number *value = Element::as_number(element);
	if (!difference || !value) return callerState.creator()->new_error("- expects numeric arguments");

	return callerState.creator()->new_number(difference->value() - value->value());
}
