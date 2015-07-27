#include "fnlist.h"

#include "pair.h"

EPtr FunctionList::apply_evaled(EPtr arguments, State &state) {
	return EPtr(arguments, state.collector());
}
