#include "fnfunctionq.h"

bool FunctionFunctionQuery::is_valid(Element *element) {
	return Element::as_function(element);
}
