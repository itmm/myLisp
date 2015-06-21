#include "fndynamic.h"

#include "identifier.h"
#include "pair.h"

void FunctionDynamic::add_to_visit(Collector::Visitor &visitor) {
	visitor.add_to_visit(_args);
	visitor.add_to_visit(_body);
}

Ptr FunctionDynamic::apply(Ptr arguments, State &state) {
	if (!_macro) {
		arguments = eval_arguments(arguments, state);
	}
	Dictionary *context = state.creator()->new_dictionary(state.root()->as_dictionary())->as_dictionary();
	Pair *cur_key = _args;
	Pair *cur_value = Element::as_pair(arguments);
	if (!cur_key || !cur_value) { return Ptr(); }

	cur_value = Element::as_pair(cur_value->cdr());
	if (!cur_value) { return  Ptr(); }

	for (; cur_key; cur_key = Element::as_pair(cur_key->cdr()), cur_value = Element::as_pair(cur_value->cdr())) {
		if (!cur_value) { return Ptr(); }
		context->put(cur_key->car()->as_identifier()->str(), cur_value->car());
	}

	Ptr new_root(context, state.collector());
	Ptr new_inserter(_macro ? state.inserter()->as_dictionary() : context, state.collector());
	State sub_state(state.creator(), new_root, new_inserter);
	Ptr body = Ptr(_body, sub_state.collector());
	return sub_state.eval(body);
}
