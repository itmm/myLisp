#include "unary.h"
#include "pair.h"


Ptr UnaryFunction::apply_evaled(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	if (! Element::as_pair(arguments)) return state.creator()->new_error("need one argument");
	if (Pair::cdr(arguments)) return state.creator()->new_error("too many arguments");
	return apply_unary(Ptr(Pair::car(arguments), state.collector()), state);
}
