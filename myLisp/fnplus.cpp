#include "fnplus.h"

#include "number.h"

Ptr FunctionPlus::empty_case(State &callerState) {
	return callerState.creator()->new_number(BigInt(0));
}

Ptr FunctionPlus::setup(State &callerState, bool &stop) {
	return callerState.creator()->new_number(BigInt(0));
}

Ptr FunctionPlus::argument_numeric(
    Ptr intermediate,
    const Fractional &element,
    State &callerState,
    bool &stop
) {
	Number *sum = Element::as_number(intermediate);
	return callerState.creator()->new_number(sum->value() + element);
}
