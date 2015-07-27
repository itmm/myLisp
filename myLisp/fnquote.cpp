#include "fnquote.h"
#include "pair.h"

EPtr FunctionQuote::apply(EPtr arguments, State &state) {
	return EPtr(Pair::car(arguments), state.collector());
}
