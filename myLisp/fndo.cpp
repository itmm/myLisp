#include "fndo.h"

#include "pair.h"

Ptr FunctionDo::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	Pair *cur = Element::as_pair(arguments);
	for (; cur && Element::as_pair(cur->cdr()); cur = cur->cdr()->as_pair()) {}
	return Ptr(Pair::car(cur), state.collector());
}
