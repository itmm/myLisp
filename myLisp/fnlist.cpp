#include "fnlist.h"

#include "pair.h"

Ptr FunctionList::apply_evaled(Ptr arguments, State &state) {
	return Ptr(arguments, state.collector());
}
