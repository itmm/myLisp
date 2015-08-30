#include "fndict.h"
#include "string.h"
#include "pair.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionDict> _creator("dict");

EPtr FunctionDict::apply_evaled(EPtr arguments, State &state) {
	Pair *current = Element::as_pair(arguments);
    Dictionary *parent = nullptr;
    if (current && (! Pair::car(current) || Element::as_dictionary(Pair::car(current)))) {
        parent = Element::as_dictionary(Pair::car(current));
        current = Element::as_pair(Pair::cdr(current));
    }
    
	EPtr result = state.creator()->new_dictionary(parent);
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
