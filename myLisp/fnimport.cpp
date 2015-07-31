#include <fstream>
#include "fnimport.h"

#import "pair.h"
#import "parser.h"
#import "string.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionImport> _creator("import");

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
    
    if (in.fail()) {
        Creator *creator = state.creator();
        EPtr car = creator->new_string("can't import");
        EPtr cdr = creator->new_pair(creator->new_string(name), nullptr);
        return creator->new_error(car, cdr);
    }
 
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
		if (!path) return state.error("string expected");
        EPtr res = import(path->str(), state);
        if (Element::as_error(res)) return res;
	}
	return state.trueNumber();
}
