#include "listable.h"

#include "pair.h"

Ptr Listable::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	if (!arguments) return empty_case(state);
	Pair *current = arguments->as_pair();
	if (!current) return state.creator()->new_error("Listable needs a plain list");

	bool stop = false;
	Ptr intermediate = setup(state, stop);
	if (stop || (_stopOnError && Element::as_error(intermediate))) return intermediate;

	intermediate = first_argument(intermediate, current->car(), current->cdr() != nullptr, state, stop);
	if (stop || (_stopOnError && Element::as_error(intermediate))) return intermediate;

	while (current->cdr()) {
		current = Element::as_pair(current->cdr());
		if (!current) return state.creator()->new_error("Listable needs a plain list");
		intermediate = argument(intermediate, current->car(), state, stop);
		if (stop || (_stopOnError && Element::as_error(intermediate))) return intermediate;
	}

	return finish(intermediate, state);
}


Ptr Listable::empty_case(State &callerState) {
	return callerState.creator()->new_error("Listable needs at least one argument");;
}

Ptr Listable::setup(State &callerState, bool &stop) {
	return Ptr();
}

Ptr Listable::first_argument(Ptr intermediate, Element *element, bool hasMore, State &callerState, bool &stop) {
	return argument(intermediate, element, callerState, stop);
}

Ptr Listable::finish(Ptr intermediate, State &callerState) {
	return intermediate;
}
