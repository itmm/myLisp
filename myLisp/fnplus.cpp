#include "fnplus.h"

#include "number.h"
#include "pair.h"

Ptr FunctionPlus::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);

	Fractional sum = 0;

	Pair *cur = Element::as_pair(arguments);
	for (; cur ; cur = Element::as_pair(cur->cdr())) {
		Number *n = Element::as_number(cur->car());
		if (!n) { return Ptr(); }
		sum = sum + n->value();
	}
	return state.creator()->new_number(sum);
}
