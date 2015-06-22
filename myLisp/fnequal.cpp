#include "fnequal.h"
#include "pair.h"
#include "number.h"

Ptr FunctionEqual::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	Pair *cur = Element::as_pair(Pair::cdr(arguments));
	if (!cur) { return state.falseNumber(); }

	Number *ref = Element::as_number(Pair::car(cur));
	if (!ref) { return Ptr(); }

	cur = Element::as_pair(Pair::cdr(cur));
	if (!cur) { return state.boolNumber(ref->value() == 0); }

	for (; cur; cur = Element::as_pair(Pair::cdr(cur))) {
		Number *num = Element::as_number(Pair::car(cur));
		if (!num) { return Ptr(); }
		if (!(num->value() == ref->value())) { return state.falseNumber(); }
	}

	return state.trueNumber();
}
