#include "fnquote.h"
#include "pair.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionQuote> _creator("quote");

EPtr FunctionQuote::apply(EPtr arguments, State &state) {
	return EPtr(Pair::car(arguments), state.collector());
}
