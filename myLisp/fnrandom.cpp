#include "fnrandom.h"

#include "function_creator.h"

SimpleFunctionCreator<FunctionRandom> randomCreator("random");

EPtr FunctionRandom::apply_unary_numeric(const Fractional &value, State &state) {
    if (value.denominator() != BigInt(1)) return state.error("argument must be integer");
    return state.creator()->new_number(value.numerator().random());
}
