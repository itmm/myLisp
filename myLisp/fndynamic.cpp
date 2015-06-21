#include "fndynamic.h"
#include "identifier.h"

Ptr FunctionDynamic::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	Dictionary *context = state.creator()->new_dictionary(state.root()->as_dictionary())->as_dictionary();
	Pair *cur_key = _args;
	Pair *cur_value = Element::as_pair(arguments);
	if (!cur_key || !cur_value) { return Ptr(); }

	cur_value = Element::as_pair(cur_value->cdr());
	if (!cur_value) { return  Ptr(); }

	for (; cur_key && cur_key != Pair::null(); cur_key = Element::as_pair(cur_key->cdr()), cur_value = Element::as_pair(cur_value->cdr())) {
		if (!cur_value) { return Ptr(); }
		context->put(cur_key->car()->as_identifier()->str(), cur_value->car());
	}

	State sub_state(state.creator(), Ptr(context, state.collector()));
	Ptr body = Ptr(_body, sub_state.collector());
	return sub_state.eval(body);
}
