#include "fnerrorq.h"

bool FunctionErrorQuery::is_valid(Element *element) {
	return Element::as_error(element);
}
