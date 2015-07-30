#include "fnnumerator.h"
#include "number.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionNumerator> _creator("numerator");

EPtr FunctionNumerator::apply_unary_numeric(const Fractional &value, State &state) {
	return state.creator()->new_number(value.numerator());
}
