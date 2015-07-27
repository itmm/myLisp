#include "listable_numeric.h"

#include "number.h"

EPtr ListableNumericFunction::first_argument(
    EPtr intermediate,
    EPtr element,
    bool hasMore,
    State &callerState,
    bool &stop
) {
    Number *value = Element::as_number(element);
    if (! value) { stop = true; return callerState.error("first argument must be numeric"); }
    return first_argument_numeric(intermediate, value->value(), hasMore, callerState, stop);
}

EPtr ListableNumericFunction::argument(EPtr intermediate, EPtr element, State &callerState, bool &stop) {
    Number *value = Element::as_number(element);
    if (! value) { stop = true; return callerState.error("argument must be numeric"); }
    return argument_numeric(intermediate, value->value(), callerState, stop);
}

EPtr ListableNumericFunction::first_argument_numeric(
    EPtr intermediate,
    const Fractional &element,
    bool hasMore,
    State &callerState,
    bool &stop
) {
    return argument_numeric(intermediate, element, callerState, stop);
}
