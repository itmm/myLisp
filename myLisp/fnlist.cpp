#include "fnlist.h"

#include "pair.h"

Ptr FunctionList::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	Pair *head = Element::as_pair(arguments);

	if (!head || head == Pair::null()) { return Ptr(); }
	return Ptr(head->cdr(), state.collector());
}
