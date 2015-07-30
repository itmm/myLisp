#include "fnplus.h"

#include "number.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionPlus> _creator("+");

EPtr FunctionPlus::empty_case(State &callerState) {
	return callerState.creator()->new_number(BigInt(0));
}

EPtr FunctionPlus::setup(State &callerState, bool &stop) {
	return callerState.creator()->new_number(BigInt(0));
}

EPtr FunctionPlus::argument_numeric(
    EPtr intermediate,
    const Fractional &element,
    State &callerState,
    bool &stop
) {
	Number *sum = Element::as_number(intermediate);
	return callerState.creator()->new_number(sum->value() + element);
}
