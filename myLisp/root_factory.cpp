#include "root_factory.h"

#include "creator.h"
#include "dictionary.h"
#include "fractional.h"
#include "fnplus.h"
#include "number.h"

Ptr RootFactory::root() {
	Dictionary *dict = _creator->new_dictionary()->as_dictionary();
	dict->put("Infinity", new Number(Fractional::infinity()));
	dict->put("NotANumber", new Number(Fractional::notANumber()));
	dict->put("+", new FunctionPlus());

	return Ptr(dict, _creator->collector());

}
