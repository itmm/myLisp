#include "fnminus.h"

#include "number.h"

Ptr FunctionMinus::empty_case(State &callerState) {
	return callerState.creator()->new_number(-Fractional(1));
}

Ptr FunctionMinus::first_argument(Ptr, Ptr element, bool hasMore, State &callerState, bool &stop) {
	Number *value = Element::as_number(element);
	if (!value) return callerState.error("- expects numeric arguments");
	return hasMore ? callerState.ptr(value) : callerState.creator()->new_number(-value->value());
}

Ptr FunctionMinus::argument(Ptr intermediate, Ptr element, State &callerState, bool &stop) {
	Number *difference = Element::as_number(intermediate);
	Number *value = Element::as_number(element);
	if (!difference || !value) return callerState.error("- expects numeric arguments");

	return callerState.creator()->new_number(difference->value() - value->value());
}
