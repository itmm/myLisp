#include "fndivide.h"
#include "number.h"

Ptr FunctionDivide::first_argument_numeric(
    Ptr,
    const Fractional &element,
    bool hasMore,
    State &callerState,
    bool &stop
) {
	return callerState.creator()->new_number(hasMore ? element : BigInt(1) / element);
}

Ptr FunctionDivide::argument_numeric(
    Ptr intermediate,
    const Fractional &element,
    State &callerState,
    bool &stop
) {
	Number *div = Element::as_number(intermediate);
	return callerState.creator()->new_number(div->value() / element);
}
