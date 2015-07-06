#include "fnequal.h"

bool FunctionEqual::is_valid(Element *last, Element *current) {
	return Element::is_equal(last, current);
}
