#include "fndict.h"
#include "string.h"
#include "pair.h"

Ptr FunctionDict::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	Pair *current = Element::as_pair(arguments);
	Ptr result = state.creator()->new_dictionary(nullptr);
	Dictionary *dict = Element::as_dictionary(result);
	for (; current; current = Element::as_pair(current->cdr())) {
		Pair *pair = Element::as_pair(current->car());
		if (! pair) return state.error("pair expected");
		if (Pair::cdr(Pair::cdr(pair))) return state.error("pair must have two elements");
		String *key = Element::as_string(Pair::car(pair));
		if (! key) return state.error("key must be a string");
		dict->put(key->str(), Pair::car(Pair::cdr(pair)));
	}
	return result;
}
