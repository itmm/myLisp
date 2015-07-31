#include "binary.h"
#include "pair.h"

EPtr BinaryFunction::apply_evaled(EPtr arguments, State &state) {
	Pair *head = Element::as_pair(arguments);
	if (! head) return state.error("no first argument");
	Pair *rest = Element::as_pair(head->cdr());
	if (! rest) return state.error("no second argument");
	if (rest->cdr()) return state.error("more than two arguments");

	return apply_binary(
	    EPtr(head->car(), state.collector()),
		EPtr(rest->car(), state.collector()),
		state
	);
}
