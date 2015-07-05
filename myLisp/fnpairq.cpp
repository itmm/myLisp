#include "fnpairq.h"

bool FunctionPairQuery::is_valid(Element *element) {
	return !element || Element::as_pair(element);
}
