#include "fnerror.h"
#include "pair.h"
#include "string.h"

Ptr FunctionError::apply(Ptr arguments, State &state) {
	Creator *c = state.creator();
	arguments = eval_arguments(arguments, state);
	if (!arguments) { return c->new_error("error must have one argument"); }
	Pair *pair = arguments->as_pair();
	if (!pair) { return c->new_error("error arguments must be a list"); }
	if (pair->cdr()) { return c->new_error("error has more than one argument"); }
	String *str = Element::as_string(pair->car());
	if (!str) { return c->new_error("error argument must be a string"); }
	return c->new_error(str->str());
}
