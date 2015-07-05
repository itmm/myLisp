#include <sstream>

#include "fnstrprint.h"
#include "pair.h"

Ptr FunctionStrPrint::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	std::ostringstream buffer;
	std::string separator;

	Pair *cur = Element::as_pair(arguments);
	for (; cur; cur = Element::as_pair(cur->cdr())) {
		buffer << separator << Ptr(cur->car(), state.collector());
		separator = " ";
	}
	return state.creator()->new_string(buffer.str());
}
