#include "fnquote.h"
#include "pair.h"

Ptr FunctionQuote::apply(Ptr arguments, State &state) {
	return Ptr(Pair::car(Pair::cdr(arguments)), state.collector());
}
