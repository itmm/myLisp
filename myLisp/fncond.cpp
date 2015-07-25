#include "fncond.h"
#include "pair.h"

Ptr FunctionCond::apply(Ptr arguments, State &state) {
	for (Pair *cur = Element::as_pair(arguments); cur; cur = Element::as_pair(cur->cdr())) {
		Pair *entry = Element::as_pair(cur->car());
		if (! entry) return state.error("entries must be pairs");
		Ptr condition = state.eval(Ptr(entry->car(), state.collector()));
		if (Element::is_true(condition)) {
			Ptr result;
			for (entry = Element::as_pair(entry->cdr()); entry; entry = Element::as_pair(entry->cdr())) {
				result = state.eval(Ptr(entry->car(), state.collector()));
			}
			return result;
		}
	}
	return state.error("unmatched cond");
}
