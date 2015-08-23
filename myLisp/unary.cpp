#include "unary.h"
#include "pair.h"

EPtr UnaryFunction::apply_evaled(EPtr arguments, State &state) {
	if (! Element::as_pair(arguments)) return state.error("need one argument");
	if (Pair::cdr(arguments)) return state.error("too many arguments");
	return apply_unary(EPtr(Pair::car(arguments), state.collector()), state);
}
