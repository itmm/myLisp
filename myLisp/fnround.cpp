#include "fnround.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionRound> _creator("round");

/*
EPtr FunctionRound::apply_evaled(EPtr arguments, State &state) {
    Number *value = Element::as_number(Pair::car(arguments));
    if (! value) return state.error("first argument must be numeric");
    BigInt fractions(5);
    Element *next = Pair::cdr(arguments);
    if (next) {
        Number *digits = Element::as_number(Pair::car(next));
        if (! digits) return state.error("second argument must be numeric");
        if (Pair::cdr(next)) return state.error("too many arguments");
        if (digits->value().denominator() != BigInt(1)) return state.error("digits must be integer");
        fractions = digits->value().numerator();
    }
    
    
}
*/

EPtr FunctionRound::apply_unary_numeric(const Fractional &value, State &state) {
    Fractional result = value;
    if (result.denominator() > BigInt(1)) {
       BigInt rest = result.numerator() % result.denominator();
       result = result - Fractional(rest, value.denominator(), value.isNegative());
    }
    return state.creator()->new_number(result);
}
