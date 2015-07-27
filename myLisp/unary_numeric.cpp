#include "unary_numeric.h"
#include "number.h"

EPtr UnaryNumericFunction::apply_unary(EPtr arg, State &callerState) {
	Number *value = Element::as_number(arg);
	if (! value) return callerState.error("argument must be a number");
	return apply_unary_numeric(value->value(), callerState);
}
