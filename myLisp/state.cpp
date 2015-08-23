#include "state.h"

#include "function.h"
#include "identifier.h"
#include "pair.h"

EPtr State::eval(EPtr expression) {
	if (Element::as_identifier(expression)) {
		expression = EPtr(_root->as_dictionary()->get(expression), collector());
	}
	Pair *pair = Element::as_pair(expression);
	if (pair) {
		Element *car = pair->car();
		Function *fn = Element::as_function(eval(ptr(car)));
		if (fn) {
			EPtr result = fn->apply(ptr(pair->cdr()), *this);
			return result;
		}
	}
	return expression;
}