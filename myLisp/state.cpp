#include "state.h"

#include "function.h"
#include "identifier.h"
#include "pair.h"

Ptr State::eval(Ptr expression) {
	if (Element::as_identifier(expression)) {
		expression = Ptr(_root->as_dictionary()->get(expression), collector());
	}
	Pair *pair = Element::as_pair(expression);
	if (pair) {
		Element *car = pair->car();
		Function *fn = Element::as_function(eval(Ptr(car, collector())));
		if (fn) {
			Ptr result = fn->apply(Ptr(pair->cdr(), collector()), *this);
			return result;
		}
	}
	return expression;
}