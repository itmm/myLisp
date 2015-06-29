#include "fnequal.h"
#include "pair.h"

Ptr FunctionEqual::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	Pair *cur = Element::as_pair(arguments);
	if (!cur) { return state.falseNumber(); }

	Element *ref = cur->car();
	if (!ref) { return state.trueNumber(); }

	cur = Element::as_pair(Pair::cdr(cur));
	if (!cur) {
		return state.boolNumber(!Element::is_true(ref));
	}

	for (; cur; cur = Element::as_pair(Pair::cdr(cur))) {
		Element *val = cur->car();
		if (!(Element::is_equal(val, ref))) { return state.falseNumber(); }
	}

	return state.trueNumber();
}
