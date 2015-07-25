#include "fncdr.h"
#include "pair.h"

Ptr FunctionCdr::apply_unary_pair(Ptr pair, State &state) {
	return state.ptr(Pair::cdr(pair));
}
