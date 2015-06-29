#include "fncar.h"

#include "pair.h"

Ptr FunctionCar::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	if (!arguments) { return state.creator()->new_error("car needs one argument"); }
	Pair *first = arguments->as_pair();
	if (!first) { return state.creator()->new_error("arguments of car are not a list"); }
	if (first->cdr()) { return state.creator()->new_error("car has more than one argument"); }
	Element *value = first->car();
	if (!value) { return Ptr(); }
	Pair *pair = value->as_pair();
	if (!pair) { return state.creator()->new_error("car's argument must be a pair"); }
	return Ptr(pair->car(), state.collector());
}
