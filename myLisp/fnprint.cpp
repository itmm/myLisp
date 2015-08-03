#include "fnprint.h"
#include "pair.h"

#include "function_creator.h"
#include "stream_handler_str.h"

class PrintFunctionCreator : public FunctionCreator {
    public:
        PrintFunctionCreator(StreamHandler *handler, const std::string key):
            FunctionCreator(key),
            _handler(handler)
        {}
    
        Function *create() override {
            return new FunctionPrint(_handler);
        }
    
    private:
        StreamHandler *_handler;
};

static PrintFunctionCreator printCreator(nullptr, "print");
static PrintFunctionCreator printErrCreator(nullptr, "err-print");
static PrintFunctionCreator printStrCreator(new StreamHandlerStr(), "str-print");

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
		*stream << separator;
        if (cur->car()) {
            cur->car()->to_stream(*stream, false);
        } else {
            *stream << "()";
        }
		separator = " ";
	}
    return state.creator()->new_string(_handler->finish(stream));
}
