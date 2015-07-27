#include "binary.h"
#include "pair.h"

EPtr BinaryFunction::apply_evaled(EPtr arguments, State &state) {
	Pair *head = Element::as_pair(arguments);
	if (! head) return state.creator()->new_error("no first argument");
	Pair *rest = Element::as_pair(head->cdr());
	if (! rest) return state.creator()->new_error("no second argument");
	if (rest->cdr()) return state.creator()->new_error("more than two arguments");

	return apply_binary(
	    EPtr(head->car(), state.collector()),
		EPtr(rest->car(), state.collector()),
		state
	);
}
