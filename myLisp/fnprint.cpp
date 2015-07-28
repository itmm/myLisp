#include "fnprint.h"
#include "pair.h"

void FunctionPrint::setHandler(StreamHandler *handler) {
    if (handler != _handler) {
        if (_handler) delete _handler;
        _handler = handler;
    }
}

FunctionPrint::~FunctionPrint() {
    setHandler(nullptr);
}

EPtr FunctionPrint::apply_evaled(EPtr arguments, State &state) {
    if (! _handler) return state.error("no stream handler");
    
	Pair *cur = Element::as_pair(arguments);
	std::string separator;
    std::ostream *stream = _handler->prepare();
	for (; cur; cur = Element::as_pair(Pair::cdr(cur))) {
		*stream << separator << EPtr(cur->car(), state.collector());
		separator = " ";
	}
    return state.creator()->new_string(_handler->finish(stream));
}
