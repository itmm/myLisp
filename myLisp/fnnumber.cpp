#include "fnnumber.h"

bool FunctionNumber::is_valid(Element *element) {
	return Element::as_number(element);
}
