#include "fntimes.h"

#include "number.h"

EPtr FunctionTimes::empty_case(State &callerState) {
	return callerState.creator()->new_number(BigInt(1));
}

EPtr FunctionTimes::setup(State &callerState, bool &stop) {
	return callerState.creator()->new_number(BigInt(1));
}

EPtr FunctionTimes::argument_numeric(
    EPtr intermediate,
    const Fractional &element,
    State &callerState,
    bool &stop
) {
	Number *product = Element::as_number(intermediate);
	return callerState.creator()->new_number(product->value() * element);
}
