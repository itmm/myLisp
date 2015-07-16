#include "fndynamic.h"

#include "identifier.h"
#include "pair.h"
#include "expander.h"

void FunctionDynamic::add_to_visit(Collector::Visitor &visitor) {
	visitor.add_to_visit(_args);
	visitor.add_to_visit(_body);
	visitor.add_to_visit(_root);
	visitor.add_to_visit(_inserter);
}

Ptr FunctionDynamic::apply(Ptr arguments, State &state) {
	if (!_macro) {
		arguments = eval_arguments(arguments, state);
	}
	Dictionary *context = state.creator()->new_dictionary(_macro ? static_cast<Dictionary *>(nullptr) : _root)->as_dictionary();

	Element *cur_key = _args;
	Element *cur_value = arguments;
	for (; Element::as_pair(cur_key); cur_key = Pair::cdr(cur_key), cur_value = Pair::cdr(cur_value)) {
		String *key = Element::as_string(Pair::car(cur_key));
		if (! key) return state.creator()->new_error("string expected as key");
		Element *value = Pair::car(cur_value);
		context->put(key->str(), value);
	}
	if (cur_key) {
		String *key = Element::as_string(cur_key);
		if (! key) return state.creator()->new_error("string expected as list key");
		context->put(key->str(), cur_value);
	}

	if (_macro) {
		Expander expander(Ptr(context, state.collector()));
		State sub_state(state.creator(), Ptr(_root, state.collector()), Ptr(_inserter, state.collector()));
		sub_state.setName("macro-call");
		Ptr body = Ptr(_body, sub_state.collector());
		Ptr body2 = expander.rewrite(body, *sub_state.creator());
		//std::cerr << body << " -> " << body2 << std::endl;

		Ptr result;
		for (Pair *cur = Element::as_pair(body2); cur; cur = Element::as_pair(cur->cdr())) {
			result = state.eval(Ptr(cur->car(), state.collector()));
		}
		return result;
	} else {
		Ptr new_root(context, state.collector());
		Ptr new_inserter(context, state.collector());
		State sub_state(state.creator(), new_root, new_inserter);
		sub_state.setName("fn-call");
		Ptr body = Ptr(_body, sub_state.collector());
		Ptr result;
		for (Pair *cur = Element::as_pair(body); cur; cur = Element::as_pair(cur->cdr())) {
			result = sub_state.eval(Ptr(cur->car(), sub_state.collector()));
		}
		return result;
	}
}
