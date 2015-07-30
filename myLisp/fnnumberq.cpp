#include "fnnumberq.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionNumberQuery> _creator("number?");

bool FunctionNumberQuery::is_valid(Element *element) {
	return Element::as_number(element);
}
