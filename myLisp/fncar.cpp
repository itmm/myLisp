#include "fncar.h"

#include "pair.h"

EPtr FunctionCar::apply_unary_pair(EPtr pair, State &state) {
	return state.ptr(Pair::car(pair));
}
