#include "fngcd.h"

Ptr FunctionGcd::apply_integers(const BigInt &first, const BigInt &second, State &state) {
	return state.creator()->new_number(gcd(first, second));
}
