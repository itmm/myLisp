#include "fnprint.h"
#include "pair.h"

Ptr FunctionPrint::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	Pair *cur = Element::as_pair(arguments);
	std::string separator;
	for (; cur; cur = Element::as_pair(Pair::cdr(cur))) {
		_stream << separator << Ptr(cur->car(), state.collector());
		separator = " ";
	}
	_stream << std::endl;
	return Ptr();
}
