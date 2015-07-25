#include "fndivide.h"
#include "number.h"

Ptr FunctionDivide::first_argument(Ptr, Ptr element, bool hasMore, State &callerState, bool &stop) {
	Number *value = Element::as_number(element);
	if (!value) return callerState.error("number expected");
	return hasMore ? Ptr(element, callerState.collector()) : callerState.creator()->new_number(BigInt(1) / value->value());
}

Ptr FunctionDivide::argument(Ptr intermediate, Ptr element, State &callerState, bool &stop) {
	Number *div = Element::as_number(intermediate);
	Number *value = Element::as_number(element);
	if (!div || !value) return callerState.error("number expected");
	return callerState.creator()->new_number(div->value() / value->value());
}
