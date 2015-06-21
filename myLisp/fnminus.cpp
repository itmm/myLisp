#include "fnminus.h"

#include "number.h"
#include "pair.h"

Ptr FunctionMinus::apply(Ptr arguments, State &state) {
    arguments = eval_arguments(arguments, state);

    Pair *head = Element::as_pair(arguments);
    if (!head) { return Ptr(); }

	if (!head->cdr()) {
		return state.creator()->new_number(-Fractional(1));
	}
    Pair *cur = Element::as_pair(head->cdr());
    if (!cur) { return Ptr(); }

    Number *n = Element::as_number(cur->car());
    if (!n) { return Ptr(); }
    Fractional sum = n->value();

	if (!cur->cdr()) {
		return state.creator()->new_number(-sum);
	}
	cur = Element::as_pair(cur->cdr());
	if (!cur) { return Ptr(); }
    for (; cur; cur = Element::as_pair(cur->cdr())) {
        n = Element::as_number(cur->car());
        if (!n) { return Ptr(); }
        sum = sum - n->value();
    }

	return state.creator()->new_number(sum);
}
