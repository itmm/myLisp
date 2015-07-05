#include "fnbool.h"

bool FunctionBool::is_valid(Element *element) {
	return Element::is_true(element) == _expected;
}
