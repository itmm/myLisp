#include "fnnumerator.h"
#include "pair.h"
#include "number.h"

Ptr FunctionNumerator::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	Number *value = Element::as_number(Pair::car(arguments));
	if (! value) return state.creator()->new_error("argument must be numeric");
	if (Pair::cdr(arguments)) return state.creator()->new_error("too many arguments");
	return state.creator()->new_number(value->value().numerator());
}
