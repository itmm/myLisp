#include "fndenominator.h"
#include "number.h"

EPtr FunctionDenominator::apply_unary_numeric(const Fractional &value, State &state) {
	return state.creator()->new_number(value.denominator());
}
