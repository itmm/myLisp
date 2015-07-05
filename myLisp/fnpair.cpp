#include "fnpair.h"

bool FunctionPair::is_valid(Element *element) {
	return !element || Element::as_pair(element);
}
