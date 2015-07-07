#include "fnless.h"

bool FunctionLess::is_valid(Element *last, Element *current) {
	return Element::is_less(last, current);
}
