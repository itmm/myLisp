#include "fnlambda.h"

#include "fndynamic.h"
#include "identifier.h"
#include "pair.h"

Ptr FunctionLambda::apply(Ptr arguments, State &state) {
	Pair *head = Element::as_pair(arguments);
	if (!head) { return Ptr(); }

	Pair *args = Element::as_pair(head->cdr());
	if (!args) { return Ptr(); }

	bool isMacro = false;
	if (Element::as_identifier(args->car()) && args->car()->as_identifier()->str() == "macro") {
		isMacro = true;
		args = Element::as_pair(args->cdr());
		if (!args) { return Ptr(); }
	}

	Pair *body = Element::as_pair(args->cdr());
	if (!body) { return Ptr(); }

	Pair *real_args;
	if (Element::as_identifier(args->car())) {
		real_args = Element::as_pair(state.root()->as_dictionary()->get(args->car()));
	} else {
		real_args = Element::as_pair(args->car());
	}
	if (!real_args) { return Ptr(); }

	Element *real_body = body->car();
	if (Element::as_identifier(real_body)) {
		real_body = state.root()->as_dictionary()->get(real_body);
	}
	if (!real_body) { return Ptr(); }

	return state.creator()->new_element(new FunctionDynamic(real_args, real_body, isMacro));
}
