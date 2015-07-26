#include "fntimes.h"

#include "number.h"

Ptr FunctionTimes::empty_case(State &callerState) {
	return callerState.creator()->new_number(BigInt(1));
}

Ptr FunctionTimes::setup(State &callerState, bool &stop) {
	return callerState.creator()->new_number(BigInt(1));
}

Ptr FunctionTimes::argument_numeric(
    Ptr intermediate,
    const Fractional &element,
    State &callerState,
    bool &stop
) {
	Number *product = Element::as_number(intermediate);
	return callerState.creator()->new_number(product->value() * element);
}
