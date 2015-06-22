#include "root_factory.h"

#include "dictionary.h"
#include "fnplus.h"
#include "fndefine.h"
#include "fnminus.h"
#include "bool.h"
#include "fnlist.h"
#include "fnlambda.h"
#include "fneval.h"
#include "fncar.h"

Ptr RootFactory::root() {
	Dictionary *dict = _creator->new_dictionary()->as_dictionary();
	dict->put("Infinity", _creator->new_number(Fractional::infinity()));
	dict->put("NotANumber", _creator->new_number(Fractional::notANumber()));
	dict->put("+", _creator->new_element(new FunctionPlus()));
    dict->put("-", _creator->new_element(new FunctionMinus()));
	dict->put("def", _creator->new_element(new FunctionDefine()));
	dict->put("true", _creator->new_element(new Bool(1)));
	dict->put("false", _creator->new_element(new Bool(0)));
	dict->put("list", _creator->new_element(new FunctionList()));
	dict->put("fn", _creator->new_element(new FunctionLambda()));
	dict->put("eval", _creator->new_element(new FunctionEval()));
	dict->put("car", _creator->new_element(new FunctionCar()));
	return Ptr(dict, _creator->collector());
}
