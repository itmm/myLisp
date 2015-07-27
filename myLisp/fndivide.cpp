#include "fndivide.h"
#include "number.h"

EPtr FunctionDivide::first_argument_numeric(
    EPtr,
    const Fractional &element,
    bool hasMore,
    State &callerState,
    bool &stop
) {
	return callerState.creator()->new_number(hasMore ? element : BigInt(1) / element);
}

EPtr FunctionDivide::argument_numeric(
    EPtr intermediate,
    const Fractional &element,
    State &callerState,
    bool &stop
) {
	Number *div = Element::as_number(intermediate);
	return callerState.creator()->new_number(div->value() / element);
}
