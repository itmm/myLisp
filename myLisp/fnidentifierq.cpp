#include "fnidentifierq.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionIdentifierQuery> _creator("identifier?");

bool FunctionIdentifierQuery::is_valid(Element *element) {
	return Element::as_identifier(element);
}
