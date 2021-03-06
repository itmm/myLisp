#include "fnlet.h"

#include "pair.h"
#include "string.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionLet> _creator("let");

EPtr FunctionLet::apply(EPtr arguments, State &state) {
    if (! Element::as_pair(arguments)) return state.error("definition expected");
    EPtr root = state.creator()->new_dictionary(Element::as_dictionary(state.root()));
    Dictionary *dict = Element::as_dictionary(root);
    State sub_state(state.creator(), root);
    for (Pair *cur = Element::as_pair(Pair::car(arguments)); cur; cur = Element::as_pair(cur->cdr())) {
        Pair *def = Element::as_pair(Pair::car(cur));
        if (! def) return state.error("definition must be pair");
        String *key = Element::as_string(def->car());
        if (! key) return state.error("key must be string");
        def = Element::as_pair(def->cdr());
        if (! def) return state.error("no value present");
        Element *value = state.eval(sub_state.ptr(def->car()));
        if (def->cdr()) return state.error("too many values");
        dict->add(key->str(), value);
    }
    EPtr result;
    for (Pair *cur = Element::as_pair(Pair::cdr(arguments)); cur; cur = Element::as_pair(cur->cdr())) {
        result = sub_state.eval(sub_state.ptr(cur->car()));
    }
    return result;
}
