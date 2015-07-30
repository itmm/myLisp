#include "fnerrorq.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionErrorQuery> _creator("error?");

bool FunctionErrorQuery::is_valid(Element *element) {
	return Element::as_error(element);
}
