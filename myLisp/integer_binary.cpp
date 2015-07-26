#include "integer_binary.h"

Ptr IntegerBinaryFunction::apply_binary(const Fractional &first, const Fractional &second, State &state) {
	static BigInt one(1);
	if (first.denominator() != one) return state.error("first argument must be integer");
	if (second.denominator() != one) return state.error("second argument must be integer");
	return apply_integers(first.numerator(), second.numerator(), state);
}
