#include "listable_numeric.h"

#include "number.h"

Ptr ListableNumericFunction::first_argument(
    Ptr intermediate,
    Ptr element,
    bool hasMore,
    State &callerState,
    bool &stop
) {
    Number *value = Element::as_number(element);
    if (! value) { stop = true; return callerState.error("first argument must be numeric"); }
    return first_argument_numeric(intermediate, value->value(), hasMore, callerState, stop);
}

Ptr ListableNumericFunction::argument(Ptr intermediate, Ptr element, State &callerState, bool &stop) {
    Number *value = Element::as_number(element);
    if (! value) { stop = true; return callerState.error("argument must be numeric"); }
    return argument_numeric(intermediate, value->value(), callerState, stop);
}

Ptr ListableNumericFunction::first_argument_numeric(
    Ptr intermediate,
    const Fractional &element,
    bool hasMore,
    State &callerState,
    bool &stop
) {
    return argument_numeric(intermediate, element, callerState, stop);
}
