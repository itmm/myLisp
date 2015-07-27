#include "fncond.h"
#include "pair.h"

EPtr FunctionCond::apply(EPtr arguments, State &state) {
	for (Pair *cur = Element::as_pair(arguments); cur; cur = Element::as_pair(cur->cdr())) {
		Pair *entry = Element::as_pair(cur->car());
		if (! entry) return state.error("entries must be pairs");
		EPtr condition = state.eval(EPtr(entry->car(), state.collector()));
		if (Element::is_true(condition)) {
			EPtr result;
			for (entry = Element::as_pair(entry->cdr()); entry; entry = Element::as_pair(entry->cdr())) {
				result = state.eval(state.ptr(entry->car()));
			}
			return result;
		}
	}
	return state.error("unmatched cond");
}
