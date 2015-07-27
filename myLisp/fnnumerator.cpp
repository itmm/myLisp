#include "fnnumerator.h"
#include "number.h"

EPtr FunctionNumerator::apply_unary_numeric(const Fractional &value, State &state) {
	return state.creator()->new_number(value.numerator());
}
