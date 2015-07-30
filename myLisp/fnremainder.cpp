#include "fnremainder.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionRemainder> _creator("remainder");

EPtr FunctionRemainder::apply_integers(const BigInt &first, const BigInt &second, State &state) {
	return state.creator()->new_number(first % second);
}
