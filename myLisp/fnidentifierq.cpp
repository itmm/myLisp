#include "fnidentifierq.h"

bool FunctionIdentifierQuery::is_valid(Element *element) {
	return Element::as_identifier(element);
}
