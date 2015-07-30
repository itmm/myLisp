#include "fnless.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionLess> _creator("<");

bool FunctionLess::is_valid(Element *last, Element *current) {
	return Element::is_less(last, current);
}
