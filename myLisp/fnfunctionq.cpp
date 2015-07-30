#include "fnfunctionq.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionFunctionQuery> _creator("function?");

bool FunctionFunctionQuery::is_valid(Element *element) {
	return Element::as_function(element);
}
