#include "fnexpand.h"
#include "pair.h"
#include "expander.h"

Ptr FunctionExpand::apply(Ptr arguments, State &state) {
	if (Pair::cdr(Pair::cdr(arguments))) return state.creator()->new_error("expand needs two arguments");
	Dictionary *dictionary = Element::as_dictionary(state.eval(Ptr(Pair::car(arguments), state.collector())));
	if (! dictionary) return state.creator()->new_error("first argument must be dictionary");
	Element *root = Pair::car(Pair::cdr(arguments));
	Expander expander(Ptr(dictionary, state.collector()));
	return expander.rewrite(Ptr(root, state.collector()), *state.creator());
}
