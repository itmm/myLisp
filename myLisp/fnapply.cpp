#include "fnapply.h"
#include "pair.h"

Ptr FunctionApply::apply_binary(Ptr first, Ptr second, State &state) {
	Function *fn = Element::as_function(first);
	if (! fn) return state.error("first argument must be function");
	Pair *args = Element::as_pair(second);
	if (! args && second) return state.error("second argument must be a pair");
	return fn->apply(state.ptr(args), state);
}
