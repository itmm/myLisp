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
	Element *real_args = state.eval(Ptr(args->car(), state.collector()));
	// std::cerr << "args == " << Ptr(real_args, state.collector()) << std::endl;
	return state.creator()->new_element(new FunctionDynamic(real_args, body, isMacro, state));
}
