#include "fnremainder.h"

Ptr FunctionRemainder::apply_integers(const BigInt &first, const BigInt &second, State &state) {
	return state.creator()->new_number(first % second);
}
