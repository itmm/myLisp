#include "fnlambda.h"

#include "fndynamic.h"
#include "identifier.h"
#include "pair.h"
#include "string.h"

Ptr FunctionLambda::apply(Ptr arguments, State &state) {
	Pair *args = Element::as_pair(arguments);
	if (!args) { return Ptr(); }

	bool isMacro = false;
	if (Element::as_identifier(args->car()) && args->car()->as_identifier()->str() == "macro") {
		isMacro = true;
		args = Element::as_pair(args->cdr());
		if (!args) { return Ptr(); }
	}

	Pair *body = Element::as_pair(args->cdr());
	if (!body) { return Ptr(); }

	Element *real_args = state.eval(Ptr(args->car(), state.collector()));
	bool var_args = Element::as_string(real_args);

	Element *real_body = body->car();
	if (Element::as_identifier(real_body)) {
		real_body = state.root()->as_dictionary()->get(real_body);
	}
	if (!real_body) { return Ptr(); }

	return state.creator()->new_element(new FunctionDynamic(real_args, var_args, real_body, isMacro, state));
}
