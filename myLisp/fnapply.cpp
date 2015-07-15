#include "fnapply.h"
#include "pair.h"

Ptr FunctionApply::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	Function *fn = Element::as_function(Pair::car(arguments));
	if (! fn) return state.creator()->new_error("first argument must be function");
	Pair *args = Element::as_pair(Pair::car(Pair::cdr(arguments)));
	return fn->apply(Ptr(args, state.collector()), state);
}
