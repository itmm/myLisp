#include <fstream>
#include "fnimport.h"

#import "pair.h"
#import "parser.h"
#import "string.h"

FunctionImport::~FunctionImport() {
    setHandler(nullptr);
}

void FunctionImport::setHandler(ImportHandler *handler) {
    if (handler != _handler) {
        if (_handler) delete _handler;
        _handler = handler;
    }
}

EPtr FunctionImport::import(const std::string &name, State &state) {
	Parser parser(&state);
    std::ifstream in(_handler->find_path(name.c_str()));
    if (in.fail()) return state.creator()->new_error("can't import " + name);
 
    for (;;) {
        EPtr res = parser.parse(in);
        if (!res) break;
        res = state.eval(res);
        if (Element::as_error(res)) return res;
    }
    return state.trueNumber();
}

EPtr FunctionImport::apply_evaled(EPtr arguments, State &state) {
	for (Element *cur = Element::as_pair(arguments); cur; cur = Pair::cdr(cur)) {
		String *path = Pair::car(cur)->as_string();
		if (!path) return state.creator()->new_error("string expected");
        EPtr res = import(path->str(), state);
        if (Element::as_error(res)) return res;
	}
	return state.trueNumber();
}
