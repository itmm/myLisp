#include "unary_pair.h"

EPtr UnaryPairFunction::apply_unary(EPtr arg, State &callerState) {
	if (arg && ! Element::as_pair(arg)) return callerState.error("argument must be a pair");
	return apply_unary_pair(arg, callerState);
}
