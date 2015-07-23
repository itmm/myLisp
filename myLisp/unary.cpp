#include "unary.h"
#include "pair.h"

Ptr UnaryFunction::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	if (! arguments) return state.creator()->new_error("need one argument");
	if (Pair::cdr(arguments)) return state.creator()->new_error("too many arguments");
	return applyUnary(Ptr(Pair::car(arguments), state.collector()), state);
}
