#include "fndenominator.h"
#include "number.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionDenominator> _creator("denominator");

EPtr FunctionDenominator::apply_unary_numeric(const Fractional &value, State &state) {
	return state.creator()->new_number(value.denominator());
}
