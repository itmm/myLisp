#include "fnequal.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionEqual> _creator("=");

bool FunctionEqual::is_valid(Element *last, Element *current) {
	return Element::is_equal(last, current);
}
