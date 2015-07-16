#include "fndefine.h"

#include "pair.h"
#include "string.h"

Ptr FunctionDefine::apply(Ptr arguments, State &state) {
	Pair *cur = Element::as_pair(arguments);
	if (!cur) return state.creator()->new_error("arguments must be a list");

	Element *name = state.eval(Ptr(cur->car(), state.collector()));
	if (! Element::as_string(name)) return state.creator()->new_error("first argument must eval to string");
	cur = Element::as_pair(cur->cdr());

	if (!cur) { return Ptr(); }

	Ptr value = Ptr(cur->car(), state.collector());
	value = state.eval(value);

	// std::cerr << name << " -> " << value << std::endl;

	state.inserter()->as_dictionary()->put(name->as_string()->str(), value);

	return value;
}
