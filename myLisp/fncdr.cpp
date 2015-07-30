#include "fncdr.h"
#include "pair.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionCdr> _creator("cdr");

EPtr FunctionCdr::apply_unary_pair(EPtr pair, State &state) {
	return state.ptr(Pair::cdr(pair));
}
