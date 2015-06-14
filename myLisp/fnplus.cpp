#include "fnplus.h"

#include "pair.h"
#include "fractional.h"
#include "number.h"

Ptr FunctionPlus::apply(Ptr arguments, Creator *creator) {
	if (!creator || !arguments || !arguments->as_pair()) { return Ptr(); }

	Fractional sum = 0;

	arguments = eval_arguments(arguments, creator);

	Pair *cur = arguments->as_pair()->cdr()->as_pair();
	for (; cur && cur != Pair::null(); cur = cur->cdr()->as_pair()) {
		Number *n = cur->car()->as_number();
		if (!n) { return Ptr(); }
		sum = sum + n->value();
	}
	if (cur == Pair::null()) {
		return creator->new_number(sum);
	} else {
		return Ptr();
	}
}
