#include "binary.h"
#include "pair.h"

Ptr BinaryFunction::apply_evaled(Ptr arguments, State &state) {
	Pair *head = Element::as_pair(arguments);
	if (! head) return state.creator()->new_error("no first argument");
	Pair *rest = Element::as_pair(head->cdr());
	if (! rest) return state.creator()->new_error("no second argument");
	if (rest->cdr()) return state.creator()->new_error("more than two arguments");

	return apply_binary(
	    Ptr(head->car(), state.collector()),
		Ptr(rest->car(), state.collector()),
		state
	);
}
