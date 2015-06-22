#include "fncdr.h"
#include "pair.h"

Ptr FunctionCdr::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	return Ptr(Pair::cdr(Pair::car(Pair::cdr(arguments))), state.collector());
}
