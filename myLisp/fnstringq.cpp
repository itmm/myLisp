#include "fnstringq.h"

bool FunctionStringQuery::is_valid(Element *element) {
	return Element::as_string(element);
}
