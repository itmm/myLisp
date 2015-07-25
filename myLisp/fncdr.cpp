#include "fncdr.h"
#include "pair.h"

Ptr FunctionCdr::apply_unary_pair(Ptr pair, State &state) {
	return Ptr(Pair::cdr(pair), state.collector());
}
