#include "fndictionaryq.h"

bool FunctionDictionaryQuery::is_valid(Element *element) {
	return Element::as_dictionary(element);
}
