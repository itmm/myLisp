#include "fnminus.h"

#include "number.h"

Ptr FunctionMinus::empty_case(State &callerState) {
	return callerState.creator()->new_number(-Fractional(1));
}

Ptr FunctionMinus::first_argument_numeric(
    Ptr,
    const Fractional &element,
    bool hasMore,
    State &callerState,
    bool &stop
) {
	return callerState.creator()->new_number(hasMore ? element : -element);
}

Ptr FunctionMinus::argument_numeric(
    Ptr intermediate,
    const Fractional &element,
    State &callerState,
    bool &stop
) {
	Number *difference = Element::as_number(intermediate);
	return callerState.creator()->new_number(difference->value() - element);
}
