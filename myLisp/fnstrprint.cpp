#include <sstream>

#include "fnstrprint.h"
#include "pair.h"

EPtr FunctionStrPrint::apply(EPtr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	std::ostringstream buffer;
	std::string separator;

	Pair *cur = Element::as_pair(arguments);
	for (; cur; cur = Element::as_pair(cur->cdr())) {
		buffer << separator << EPtr(cur->car(), state.collector());
		separator = " ";
	}
	return state.creator()->new_string(buffer.str());
}
