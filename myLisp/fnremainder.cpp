#include "fnremainder.h"

Ptr FunctionRemainder::apply_binary(const Fractional &first, const Fractional &second, State &state) {
	if (! (first.denominator() == BigInt(1))) return state.creator()->new_error("first argument must be integer");
	if (! (second.denominator() == BigInt(1))) return state.creator()->new_error("second argument must be integer");
	return state.creator()->new_number(first.numerator() % second.numerator());
}
