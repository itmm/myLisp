#include "fneval.h"

#include "pair.h"

Ptr FunctionEval::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	Pair *result = Element::as_pair(arguments);
	if (!result) { return Ptr(); }
	return Ptr(result->car(), state.collector());
}
