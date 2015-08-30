#include "fnget.h"

#include "dictionary.h"
#include "function_creator.h"
#include "string.h"

static SimpleFunctionCreator<FunctionGet> _creator("get");

EPtr FunctionGet::apply_binary(EPtr first, EPtr second, State &state) {
    Dictionary *dict = Element::as_dictionary(first);
    if (! dict) return state.error("first argument must be a dictionary");
    String *key = Element::as_string(second);
    if (! key) return state.error("second argument must be a string");
    return state.ptr(dict->get(key->str()));
}
