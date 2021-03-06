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

EPtr FunctionDynamic::apply(EPtr arguments, State &state) {
	if (!_macro) {
		arguments = eval_arguments(arguments, state);
	}
	Dictionary *context = state.creator()->new_dictionary(_macro ? static_cast<Dictionary *>(nullptr) : _root)->as_dictionary();

    context->add("self", this);
    
	Element *cur_key = _args;
	Element *cur_value = arguments;
	for (; Element::as_pair(cur_key); cur_key = Pair::cdr(cur_key), cur_value = Pair::cdr(cur_value)) {
		String *key = Element::as_string(Pair::car(cur_key));
		if (! key) return state.error("string expected as key");
		if (! cur_value) return state.error("too few arguments");
		Element *value = Pair::car(cur_value);
		context->add(key->str(), value);
	}
	if (cur_key) {
		String *key = Element::as_string(cur_key);
		if (! key) return state.error("string expected as list key");
		context->add(key->str(), cur_value);
	} else if (cur_value) {
		return state.error("too many arguments");
	}

	if (_macro) {
		Expander expander(EPtr(context, state.collector()));
		State sub_state(state.creator(), EPtr(_root, state.collector()), EPtr(_inserter, state.collector()));
		sub_state.setName("macro-call");
		EPtr body = EPtr(_body, sub_state.collector());
		EPtr body2 = expander.rewrite(body, *sub_state.creator());

		EPtr result;
		for (Pair *cur = Element::as_pair(body2); cur; cur = Element::as_pair(cur->cdr())) {
			result = state.eval(state.ptr(cur->car()));
		}
		return result;
	} else {
		EPtr new_root(context, state.collector());
		EPtr new_inserter(context, state.collector());
		State sub_state(state.creator(), new_root, new_inserter);
		sub_state.setName("fn-call");
		EPtr body = EPtr(_body, sub_state.collector());
		EPtr result;
		for (Pair *cur = Element::as_pair(body); cur; cur = Element::as_pair(cur->cdr())) {
			result = sub_state.eval(EPtr(cur->car(), sub_state.collector()));
		}
		return result;
	}
}

void FunctionDynamic::to_stream(std::ostream &stream, bool) const {
	stream << "(fn ";
    if (_macro) { stream << "macro "; }
	if (_args) { _args->to_stream(stream, true); } else { stream << "()"; }
	stream << ' ';
    Pair *body = Element::as_pair(_body);
	if (body) { body->to_stream_without_parenthesis(stream, true); }
	stream << ')';
}
