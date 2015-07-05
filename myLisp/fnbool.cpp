#include "fnbool.h"
#include "pair.h"

Ptr FunctionBool::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	if (!arguments) return state.creator()->new_error("bool function needs at least one argument");
	Pair *cur = arguments->as_pair();
	if (!cur) return state.creator()->new_error("bool function needs an argument list");
	for (; cur; cur = Element::as_pair(cur->cdr())) {

		if (cur->cdr() && !cur->cdr()->as_pair()) return state.creator()->new_error("bool function needs an argument list");

		if (Element::is_true(cur->car()) != _expected) {
			return state.falseNumber();
		}
	}
	return state.trueNumber();
}
