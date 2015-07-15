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
	Pair *cur_value = Element::as_pair(arguments);

	if (_var_args) {
		Element *value = cur_value;
		context->put(_args->as_string()->str(), value);
	} else {
		Pair *cur_key = Element::as_pair(_args);
		for (; cur_key; cur_key = Element::as_pair(cur_key->cdr()), cur_value = Element::as_pair(Pair::cdr(cur_value))) {
			Element *value = cur_value->car();
			if (Element::as_string(value)) {
				value = _root->get(value);
			}
			context->put(cur_key->car()->as_string()->str(), value);
		}
	}
	if (_macro) {
		Expander expander(Ptr(context, state.collector()));
		State sub_state(state.creator(), Ptr(_root, state.collector()), Ptr(_inserter, state.collector()));
		sub_state.setName("macro-call");
		Ptr body = Ptr(_body, sub_state.collector());
		Ptr body2 = expander.rewrite(body, *sub_state.creator());
		//std::cerr << body << " -> " << body2 << std::endl;
		Ptr result = state.eval(body2);
		return result;
	} else {
		Ptr new_root(context, state.collector());
		Ptr new_inserter(context, state.collector());
		State sub_state(state.creator(), new_root, new_inserter);
		sub_state.setName("fn-call");
		Ptr body = Ptr(_body, sub_state.collector());
		Ptr result = sub_state.eval(body);
		return result;
	}
}
