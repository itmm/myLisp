#include "fncar.h"

#include "pair.h"

Ptr FunctionCar::apply_unary_pair(Ptr pair, State &state) {
	return state.ptr(Pair::car(pair));
}
