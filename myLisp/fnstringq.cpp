#include "fnstringq.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionStringQuery> _creator("string?");

bool FunctionStringQuery::is_valid(Element *element) {
	return Element::as_string(element);
}
