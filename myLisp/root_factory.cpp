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
#include "fncond.h"
#include "fncdr.h"
#include "fnequal.h"
#include "fnquote.h"
#include "fnimport.h"
#include "fnerror.h"
#include "fntimes.h"
#include "fnprint.h"
#include "fnboolq.h"
#include "fnstrprint.h"
#include "fnpairq.h"
#include "fnstringq.h"
#include "fnnumberq.h"
#include "fnfunctionq.h"
#include "fnerrorq.h"
#include "fnidentifierq.h"
#include "fndictionaryq.h"
#include "fnless.h"
#include "fnand.h"
#include "fndict.h"
#include "fnexpand.h"
#include "fnapply.h"
#include "fndivide.h"
#include "fnnumerator.h"
#include "fndenominator.h"

Ptr RootFactory::root() {
	Dictionary *dict = _creator->new_dictionary()->as_dictionary();
	dict->put("+", _creator->new_element(new FunctionPlus()));
    dict->put("-", _creator->new_element(new FunctionMinus()));
	dict->put("def", _creator->new_element(new FunctionDefine()));
	dict->put("true", _creator->new_element(new Bool(BigInt(1))));
	dict->put("false", _creator->new_element(new Bool(BigInt(0))));
	dict->put("list", _creator->new_element(new FunctionList()));
	dict->put("fn", _creator->new_element(new FunctionLambda()));
	dict->put("eval", _creator->new_element(new FunctionEval()));
	dict->put("car", _creator->new_element(new FunctionCar()));
	dict->put("cond", _creator->new_element(new FunctionCond()));
	dict->put("cdr", _creator->new_element(new FunctionCdr()));
	dict->put("=", _creator->new_element(new FunctionEqual()));
	dict->put("quote", _creator->new_element(new FunctionQuote()));
	dict->put("import", _creator->new_element(new FunctionImport()));
	dict->put("error", _creator->new_element(new FunctionError()));
	dict->put("*", _creator->new_element(new FunctionTimes()));
	dict->put("print", _creator->new_element(new FunctionPrint(std::cout)));
	dict->put("err-print", _creator->new_element(new FunctionPrint(std::cerr)));
	dict->put("true?", _creator->new_element(new FunctionBoolQuery(true)));
	dict->put("false?", _creator->new_element(new FunctionBoolQuery(false)));
	dict->put("str-print", _creator->new_element(new FunctionStrPrint()));
	dict->put("pair?", _creator->new_element(new FunctionPairQuery()));
	dict->put("string?", _creator->new_element(new FunctionStringQuery()));
	dict->put("number?", _creator->new_element(new FunctionNumberQuery()));
	dict->put("function?", _creator->new_element(new FunctionFunctionQuery()));
	dict->put("error?", _creator->new_element(new FunctionErrorQuery()));
	dict->put("identifier?", _creator->new_element(new FunctionIdentifierQuery()));
	dict->put("dictionary?", _creator->new_element(new FunctionDictionaryQuery()));
	dict->put("<", _creator->new_element(new FunctionLess()));
	dict->put("and", _creator->new_element(new FunctionAnd()));
	dict->put("dict", _creator->new_element(new FunctionDict()));
	dict->put("expand", _creator->new_element(new FunctionExpand()));
	dict->put("apply", _creator->new_element(new FunctionApply()));
	dict->put("/", _creator->new_element(new FunctionDivide()));
	dict->put("numerator", _creator->new_element(new FunctionNumerator()));
	dict->put("denominator", _creator->new_element(new FunctionDenominator()));

	return Ptr(dict, _creator->collector());
}
