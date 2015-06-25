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
		if (Element::as_identifier(car)) {
			car = Ptr(_root->as_dictionary()->get(car), collector());
		}
		Function *fn = Element::as_function(car);
		if (fn) {
			return fn->apply(Ptr(pair->cdr(), collector()), *this);
		}
	}
	return expression;
}