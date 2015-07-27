#include "listable.h"

#include "pair.h"

EPtr Listable::apply(EPtr arguments, State &state) {
	if (! arguments) return empty_case(state);
	Pair *current = arguments->as_pair();
	if (! current) return state.error("Listable needs a plain list");

	bool stop = false;
	EPtr intermediate = setup(state, stop);
	if (stop || (_stopOnError && Element::as_error(intermediate))) return intermediate;

	intermediate = first_argument(intermediate, state.eval(EPtr(current->car(), state.collector())), current->cdr() != nullptr, state, stop);
	if (stop || (_stopOnError && Element::as_error(intermediate))) return intermediate;

	while (current->cdr()) {
		current = Element::as_pair(current->cdr());
		if (!current) return state.error("Listable needs a plain list");
		intermediate = argument(intermediate, state.eval(EPtr(current->car(), state.collector())), state, stop);
		if (stop || (_stopOnError && Element::as_error(intermediate))) return intermediate;
	}

	return finish(intermediate, state);
}


EPtr Listable::empty_case(State &callerState) {
	return callerState.error("Listable needs at least one argument");;
}

EPtr Listable::setup(State &callerState, bool &stop) {
	return EPtr();
}

EPtr Listable::first_argument(EPtr intermediate, EPtr element, bool, State &callerState, bool &stop) {
	return argument(intermediate, element, callerState, stop);
}

EPtr Listable::finish(EPtr intermediate, State &callerState) {
	return intermediate;
}
