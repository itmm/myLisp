#include "fncond.h"
#include "pair.h"

Ptr FunctionCond::apply(Ptr arguments, State &state) {
	Pair *cur = Element::as_pair(arguments);
	for (;;) {
		Element *cond = Pair::car(cur);
		cur = Element::as_pair(Pair::cdr(cur));
		if (!cond) { return Ptr(); }
		Ptr evaled = state.eval(Ptr(cond, state.collector()));
		if (Element::is_true(evaled)) {
			return state.eval(Ptr(Pair::car(cur), state.collector()));
		} else {
			cur = Element::as_pair(Pair::cdr(cur));
		}
	}
}
