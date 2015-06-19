#include "fndefine.h"
#include "string.h"

Ptr FunctionDefine::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);

	Pair *head = Element::as_pair(arguments);
	if (!head) { return Ptr(); }

	Pair *cur = Element::as_pair(head->cdr());
	if (!cur) { return Ptr(); }

	String *name = Element::as_string(cur->car());
	if (!name) { return Ptr(); }

	cur = Element::as_pair(cur->cdr());
	if (!cur) { return Ptr(); }
	Element *value = cur->car();
	if (!value) { return Ptr(); }

	state.root()->as_dictionary()->put(name->str(), value);

	return Ptr(value, state.collector());
}
