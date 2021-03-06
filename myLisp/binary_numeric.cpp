#include "binary_numeric.h"
#include "number.h"

EPtr BinaryNumericFunction::apply_binary(EPtr first, EPtr second, State &state) {
	Number *first_num = Element::as_number(first);
	if (! first_num) return state.error("first argument not numeric");
	Number *second_num = Element::as_number(second);
	if (! second_num) return state.error("second argument not numeric");
	return apply_binary(first_num->value(), second_num->value(), state);
}
