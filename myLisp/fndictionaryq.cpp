#include "fndictionaryq.h"

#include "function_creator.h"

static SimpleFunctionCreator<FunctionDictionaryQuery> _creator("dictionary?");

bool FunctionDictionaryQuery::is_valid(Element *element) {
	return Element::as_dictionary(element);
}
