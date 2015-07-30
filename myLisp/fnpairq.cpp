#include "fnpairq.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionPairQuery> _creator("pair?");

bool FunctionPairQuery::is_valid(Element *element) {
	return !element || Element::as_pair(element);
}
