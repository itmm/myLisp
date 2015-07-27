#include "function.h"

#include "Pair.h"

Function *Function::as_function() {
	return this;
}

void Function::to_stream(std::ostream &stream, bool) const {
	stream << "[#FUNCTION#]";
}

EPtr Function::apply(EPtr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	return apply_evaled(arguments, state);
}

EPtr Function::apply_evaled(EPtr arguments, State &state) {
	return arguments;
}

EPtr Function::eval_arguments(EPtr arguments, State &state) {
	Pair *pair = Element::as_pair(arguments);
	if (!pair) {
		return arguments ? state.eval(arguments) : arguments;
	}

	EPtr old_cdr = EPtr(pair->cdr(), state.collector());
	EPtr old_car = EPtr(pair->car(), state.collector());
	EPtr new_car = state.eval(old_car);
	EPtr new_cdr = eval_arguments(old_cdr, state);
	if (new_car != old_car || new_cdr != old_cdr) {
		return state.creator()->new_pair(new_car, new_cdr);
	} else {
		return arguments;
	}
}
