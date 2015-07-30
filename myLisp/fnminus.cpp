#include "fnminus.h"

#include "number.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionMinus> _creator("-");

EPtr FunctionMinus::empty_case(State &callerState) {
	return callerState.creator()->new_number(-Fractional(1));
}

EPtr FunctionMinus::first_argument_numeric(
    EPtr,
    const Fractional &element,
    bool hasMore,
    State &callerState,
    bool &stop
) {
	return callerState.creator()->new_number(hasMore ? element : -element);
}

EPtr FunctionMinus::argument_numeric(
    EPtr intermediate,
    const Fractional &element,
    State &callerState,
    bool &stop
) {
	Number *difference = Element::as_number(intermediate);
	return callerState.creator()->new_number(difference->value() - element);
}
