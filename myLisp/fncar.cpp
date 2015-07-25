#include "fncar.h"

#include "pair.h"

Ptr FunctionCar::apply_unary_pair(Ptr pair, State &state) {
	return Ptr(Pair::car(pair), state.collector());
}
