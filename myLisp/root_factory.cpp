#include "root_factory.h"

#include "dictionary.h"
#include "bool.h"

#include "function_pool.h"

EPtr RootFactory::root() {
	Dictionary *dict = _creator->new_dictionary()->as_dictionary();

	dict->put("true", _creator->new_element(new Bool(BigInt(1))));
	dict->put("false", _creator->new_element(new Bool(BigInt(0))));
    
    FunctionPool::insert_functions(dict, _creator);
    
	return EPtr(dict, _creator->collector());
}
