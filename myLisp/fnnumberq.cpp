#include "fnnumberq.h"

bool FunctionNumberQuery::is_valid(Element *element) {
	return Element::as_number(element);
}
