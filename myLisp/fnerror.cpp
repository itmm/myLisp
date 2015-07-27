#include "fnerror.h"
#include "string.h"

EPtr FunctionError::apply_unary(EPtr arg, State &callerState) {
	String *str = Element::as_string(arg);
	if (!str) { return callerState.error("error argument must be a string"); }
	return callerState.error(str->str());
}
