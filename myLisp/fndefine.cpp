#include "fndefine.h"

#include "identifier.h"
#include "pair.h"

Ptr FunctionDefine::apply(Ptr arguments, State &state) {
	Pair *cur = Element::as_pair(arguments);
	if (!cur) { return Ptr(); }

	Identifier *name;

	if (Element::as_identifier(cur->car())) {
		name = cur->car()->as_identifier();
	} else {
		name = Element::as_identifier(state.eval(Ptr(cur->car(), state.collector())));
	}
	if (!name) { return Ptr(); }

	cur = Element::as_pair(cur->cdr());
	if (!cur) { return Ptr(); }

	Ptr value = Ptr(cur->car(), state.collector());
	value = state.eval(value);
	if (!value) { return Ptr(); }

	state.inserter()->as_dictionary()->put(name->str(), value);

	return Ptr(value, state.collector());
}
