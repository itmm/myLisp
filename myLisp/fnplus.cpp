#include "fnplus.h"

#include "number.h"

Ptr FunctionPlus::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);

	Pair *head = Element::as_pair(arguments);
	if (!head) { return Ptr(); }

	Fractional sum = 0;

	Pair *cur = Element::as_pair(head->cdr());
	for (; cur && cur != Pair::null(); cur = Element::as_pair(cur->cdr())) {
		Number *n = Element::as_number(cur->car());
		if (!n) { return Ptr(); }
		sum = sum + n->value();
	}
	if (cur == Pair::null()) {
		return state.creator()->new_number(sum);
	} else {
		return Ptr();
	}
}
