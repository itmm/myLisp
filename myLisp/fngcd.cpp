#include "fngcd.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionGcd> _creator("gcd");

EPtr FunctionGcd::apply_integers(const BigInt &first, const BigInt &second, State &state) {
	return state.creator()->new_number(gcd(first, second));
}
