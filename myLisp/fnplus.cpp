#include "fnplus.h"

#include "number.h"
#include "pair.h"

Ptr FunctionPlus::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);

	Pair *head = Element::as_pair(arguments);
	if (!head) { return Ptr(); }

	Fractional sum = 0;

	Pair *cur = Element::as_pair(head->cdr());
	for (; cur ; cur = Element::as_pair(cur->cdr())) {
		Number *n = Element::as_number(cur->car());
		if (!n) { return Ptr(); }
		sum = sum + n->value();
	}
	return state.creator()->new_number(sum);
}
