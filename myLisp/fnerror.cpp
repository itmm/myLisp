#include "fnerror.h"
#include "pair.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionError> _creator("error");

//             virtual EPtr apply_evaled(EPtr args, State &callerState) override;

EPtr FunctionError::apply_evaled(EPtr args, State &callerState) {
    Element *head = Pair::car(args);
    if (! head) return callerState.error("not enough arguments");
    Element *rest = Pair::cdr(args);
    
	return callerState.creator()->new_error(head, rest);
}
