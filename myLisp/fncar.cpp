#include "fncar.h"

#include "pair.h"

Ptr FunctionCar::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	return Ptr(Pair::car(Pair::car(arguments)), state.collector());
}
