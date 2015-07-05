#include "fnstring.h"

bool FunctionString::is_valid(Element *element) {
	return Element::as_string(element);
}
