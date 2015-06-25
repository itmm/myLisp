#include "fnlist.h"

#include "pair.h"

Ptr FunctionList::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	return Ptr(arguments, state.collector());
}
