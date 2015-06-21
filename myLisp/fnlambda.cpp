#include "fnlambda.h"
#include "fndynamic.h"

#include "pair.h"

Ptr FunctionLambda::apply(Ptr arguments, State &state) {
	Pair *head = Element::as_pair(arguments);
	if (!head) { return Ptr(); }

	Pair *args = Element::as_pair(head->cdr());
	if (!args) { return Ptr(); }

	Pair *body = Element::as_pair(args->cdr());
	if (!body) { return Ptr(); }

	Pair *real_args = Element::as_pair(args->car());
	if (!real_args) { return Ptr(); }

	Element *real_body = body->car();
	if (!real_body) { return Ptr(); }

	return Ptr(new FunctionDynamic(real_args, real_body), state.collector());
}
