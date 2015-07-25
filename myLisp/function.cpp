#include "function.h"

#include "Pair.h"

Function *Function::as_function() {
	return this;
}

void Function::to_stream(std::ostream &stream, bool) const {
	stream << "[#FUNCTION#]";
}

Ptr Function::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	return apply_evaled(arguments, state);
}

Ptr Function::apply_evaled(Ptr arguments, State &state) {
	return arguments;
}

Ptr Function::eval_arguments(Ptr arguments, State &state) {
	Pair *pair = Element::as_pair(arguments);
	if (!pair) {
		return arguments ? state.eval(arguments) : arguments;
	}

	Ptr old_cdr = Ptr(pair->cdr(), state.collector());
	Ptr old_car = Ptr(pair->car(), state.collector());
	Ptr new_car = state.eval(old_car);
	Ptr new_cdr = eval_arguments(old_cdr, state);
	if (new_car != old_car || new_cdr != old_cdr) {
		return state.creator()->new_pair(new_car, new_cdr);
	} else {
		return arguments;
	}
}

Ptr Function::error(const std::string &message, State &state) {
	return state.creator()->new_error(message);
}
