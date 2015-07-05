#include "fnboolq.h"

bool FunctionBoolQuery::is_valid(Element *element) {
	return Element::is_true(element) == _expected;
}
