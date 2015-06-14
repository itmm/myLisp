#include "root_factory.h"

#include "dictionary.h"
#include "fnplus.h"

Ptr RootFactory::root() {
	Dictionary *dict = _creator->new_dictionary()->as_dictionary();
	dict->put("Infinity", _creator->new_number(Fractional::infinity()));
	dict->put("NotANumber", _creator->new_number(Fractional::notANumber()));
	dict->put("+", new FunctionPlus());

	return Ptr(dict, _creator->collector());

}
