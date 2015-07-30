#include "fncar.h"

#include "pair.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionCar> _creator("car");

EPtr FunctionCar::apply_unary_pair(EPtr pair, State &state) {
	return state.ptr(Pair::car(pair));
}
