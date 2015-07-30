#include "fnexpand.h"
#include "pair.h"
#include "expander.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionExpand> _creator("expand");

EPtr FunctionExpand::apply(EPtr arguments, State &state) {
	if (Pair::cdr(Pair::cdr(arguments))) return state.creator()->new_error("expand needs two arguments");
	Dictionary *dictionary = Element::as_dictionary(state.eval(EPtr(Pair::car(arguments), state.collector())));
	if (! dictionary) return state.creator()->new_error("first argument must be dictionary");
	Element *root = Pair::car(Pair::cdr(arguments));
	Expander expander(EPtr(dictionary, state.collector()));
	return expander.rewrite(EPtr(root, state.collector()), *state.creator());
}
