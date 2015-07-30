#include "fnlist.h"

#include "pair.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionList> _creator("list");

EPtr FunctionList::apply_evaled(EPtr arguments, State &state) {
	return EPtr(arguments, state.collector());
}
