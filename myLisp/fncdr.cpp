#include "fncdr.h"
#include "pair.h"

EPtr FunctionCdr::apply_unary_pair(EPtr pair, State &state) {
	return state.ptr(Pair::cdr(pair));
}
