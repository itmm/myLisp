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
		Function *fn = Element::as_function(eval(EPtr(car, collector())));
		if (fn) {
			EPtr result = fn->apply(EPtr(pair->cdr(), collector()), *this);
			return result;
		}
	}
	return expression;
}