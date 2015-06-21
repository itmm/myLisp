#include "state.h"

#include "function.h"
#include "identifier.h"
#include "pair.h"

Ptr State::eval(Ptr expression) {
	if (Element::as_identifier(expression)) {
		expression = Ptr(_root->as_dictionary()->get(expression->as_identifier()->str()), collector());
	}
	Pair *pair = Element::as_pair(expression);
	if (pair && pair != Pair::null()) {
		Element *car = pair->car();
		if (Element::as_identifier(car)) {
			car = Ptr(_root->as_dictionary()->get(car->as_identifier()->str()), collector());
		}
		Function *fn = Element::as_function(car);
		if (fn) {
			return fn->apply(expression, *this);
		}
	}
	return expression;
}