#include "fnplus.h"

#include "number.h"
#include "pair.h"

Ptr FunctionPlus::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);

	Fractional sum = 0;

	if (arguments && !arguments->as_pair()) return state.creator()->new_error("+ expects argument list");
	Pair *cur = Element::as_pair(arguments);
	for (; cur ; cur = Element::as_pair(cur->cdr())) {
		Number *n = Element::as_number(cur->car());
		if (!n) return state.creator()->new_error("+ expects numeric arguments");
		sum = sum + n->value();
		if (cur->cdr() && !cur->cdr()->as_pair()) return state.creator()->new_error("+ expects argument list");
	}
	return state.creator()->new_number(sum);
}
