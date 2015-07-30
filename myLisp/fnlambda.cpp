#include "fnlambda.h"

#include "fndynamic.h"
#include "identifier.h"
#include "pair.h"
#include "string.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionLambda> _creator("fn");

EPtr FunctionLambda::apply(EPtr arguments, State &state) {
	Pair *args = Element::as_pair(arguments);
	if (! args) return state.error("arguments expected");

	bool isMacro = false;
    Identifier *first_argument = Element::as_identifier(args->car());
	if (first_argument && Element::as_identifier(args->car())->str() == "macro") {
		isMacro = true;
		args = Element::as_pair(args->cdr());
		if (!args) return state.error("arguments expected");
	}

	Pair *body = Element::as_pair(args->cdr());
	Element *real_args = state.eval(state.ptr(args->car()));
	return state.creator()->new_element(
        new FunctionDynamic(real_args, body, isMacro, state)
    );
}
