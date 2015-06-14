#include "state.h"

#include "function.h"

Ptr State::eval(Ptr expression) {
	Pair *pair = Element::as_pair(expression);
	if (pair && pair != Pair::null()) {
		Function *fn = Element::as_function(pair->car());
		if (fn) {
			return fn->apply(expression, *this);
		}
	}
	return expression;
}