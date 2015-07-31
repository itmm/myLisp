#include "fnnumeric.h"

#include "number.h"
#include "pair.h"

#include "function_creator.h"

#include <sstream>

static SimpleFunctionCreator<FunctionNumeric> _creator("numeric");

EPtr FunctionNumeric::apply_evaled(EPtr arguments, State &state) {
    Number *value = Element::as_number(Pair::car(arguments));
    if (! value) return state.error("first argument must be numeric");
    Fractional v = value->value();
    BigInt fractions(5);
    Element *next = Pair::cdr(arguments);
    if (next) {
        Number *digits = Element::as_number(Pair::car(next));
        if (! digits) return state.error("second argument must be numeric");
        if (Pair::cdr(next)) return state.error("too many arguments");
        if (digits->value().denominator() != BigInt(1)) return state.error("digits must be integer");
        fractions = digits->value().numerator();
    }
    
    std::ostringstream buffer;
    Fractional fraction(0);
    if (v.denominator() > BigInt(1)) {
        BigInt rest = v.numerator() % v.denominator();
        Fractional full = v - Fractional(rest, v.denominator(), v.isNegative());
        buffer << full;
        fraction = v - full;
    } else {
        buffer << v;
        fraction = Fractional(0);
    }
    buffer << ".";
    
    BigInt one(1);
    BigInt ten(10);
    for (BigInt cur(0); cur < fractions; cur = cur + one) {
        fraction = fraction * ten;
        BigInt rest = fraction.numerator() % fraction.denominator();
        Fractional full = fraction - Fractional(rest, fraction.denominator(), fraction.isNegative());
        buffer << full;
        fraction = fraction - full;
    }
    
    return state.creator()->new_string(buffer.str());
}

