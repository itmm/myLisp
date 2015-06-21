#include "fndefine.h"
#include "identifier.h"

Ptr FunctionDefine::apply(Ptr arguments, State &state) {
	Pair *head = Element::as_pair(arguments);
	if (!head) { return Ptr(); }

	Pair *cur = Element::as_pair(head->cdr());
	if (!cur) { return Ptr(); }

	Identifier *name = Element::as_identifier(cur->car());
	if (!name) { return Ptr(); }

	cur = Element::as_pair(cur->cdr());
	if (!cur) { return Ptr(); }

	Ptr value = Ptr(cur->car(), state.collector());
	value = state.eval(value);
	if (!value) { return Ptr(); }

	state.root()->as_dictionary()->put(name->str(), value);

	return Ptr(value, state.collector());
}
