#include "fnminus.h"
#include "number.h"

Ptr FunctionMinus::apply(Ptr arguments, State &state) {
    arguments = eval_arguments(arguments, state);

    Pair *head = Element::as_pair(arguments);
    if (!head) { return Ptr(); }

    Pair *cur = Element::as_pair(head->cdr());
    if (!cur) { return Ptr(); }
    if (cur == Pair::null()) {
        return state.creator()->new_number(-Fractional(1));
    }

    Number *n = Element::as_number(cur->car());
    if (!n) { return Ptr(); }
    Fractional sum = n->value();

    cur = Element::as_pair(cur->cdr());
    for (; cur && cur != Pair::null(); cur = Element::as_pair(cur->cdr())) {
        n = Element::as_number(cur->car());
        if (!n) { return Ptr(); }
        sum = sum - n->value();
    }

    if (cur == Pair::null()) {
        return state.creator()->new_number(sum);
    }
    return Ptr();
}
