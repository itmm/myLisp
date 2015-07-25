#include "unary_pair.h"

Ptr UnaryPairFunction::apply_unary(Ptr arg, State &callerState) {
	if (arg && ! Element::as_pair(arg)) return callerState.error("argument must be a pair");
	return apply_unary_pair(arg, callerState);
}
