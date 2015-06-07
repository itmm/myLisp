#include "fnplus.h"

#include "pair.h"
#include "fractional.h"
#include "number.h"

Element *FunctionPlus::apply(Element *arguments) {
	if (!arguments->as_pair()) { return nullptr; }

	Fractional sum = 0;

	Pair *cur = arguments->as_pair()->cdr()->as_pair();
	for (; cur && cur != Pair::null(); cur = cur->cdr()->as_pair()) {
		Number *n = cur->car()->as_number();
		if (!n) { return nullptr; }
		sum = sum + n->value();
	}
	if (cur == Pair::null()) {
		return new Number(sum);
	} else {
		return nullptr;
	}
}
