#include <fstream>
#include "fnimport.h"

#import "pair.h"
#import "parser.h"
#import "string.h"

Ptr FunctionImport::apply(Ptr arguments, State &state) {
	arguments = eval_arguments(arguments, state);
	Parser parser(&state);
	for (Element *cur = Element::as_pair(arguments); cur; cur = Pair::cdr(cur)) {
		String *path = Pair::car(cur)->as_string();
		if (!path) { return Ptr(); }
		std::ifstream in(path->str().c_str());
		for (;;) {
			Ptr res = parser.parse(in);
			if (!res) { break; }
			state.eval(res);
		}
	}
	return state.trueNumber();
}
