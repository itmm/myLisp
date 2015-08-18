#include "fnstrlength.h"

#include "function_creator.h"
#include "string.h"

static SimpleFunctionCreator<FunctionStringLength> _creator("_str-length");

EPtr FunctionStringLength::apply_unary(EPtr arg, State &callerState) {
    String *str = Element::as_string(arg);
    if (! str) return callerState.error("argument must be a string");
    return callerState.creator()->new_number(Fractional(str->str().size()));
}

