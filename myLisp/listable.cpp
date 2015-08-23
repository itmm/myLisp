#include "listable.h"
#include "identifier.h"

#include "pair.h"

EPtr ListableFunction::apply(EPtr arguments, State &state) {
    if (Element::as_identifier(arguments)) {
        arguments = state.ptr(state.root()->as_dictionary()->get(arguments->as_identifier()->str()));
    }
	if (! arguments) return empty_case(state);
	Pair *current = Element::as_pair(arguments);
	if (! current) {
        return state.error("Listable needs a plain list");
    }

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


EPtr ListableFunction::empty_case(State &callerState) {
	return callerState.error("Listable needs at least one argument");;
}

EPtr ListableFunction::setup(State &callerState, bool &stop) {
	return EPtr();
}

EPtr ListableFunction::first_argument(EPtr intermediate, EPtr element, bool, State &callerState, bool &stop) {
	return argument(intermediate, element, callerState, stop);
}

EPtr ListableFunction::finish(EPtr intermediate, State &callerState) {
	return intermediate;
}
