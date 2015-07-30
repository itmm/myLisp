#include "fnboolq.h"

#include "function_creator.h"

class BoolFunctionCreator : public FunctionCreator {
    public:
        BoolFunctionCreator(bool value, const std::string key):
            FunctionCreator(key),
            _value(value)
        {}
    
        Function *create() override {
            return new FunctionBoolQuery(_value);
        }
    
    private:
        bool _value;
};

static BoolFunctionCreator trueCreator(true, "true?");
static BoolFunctionCreator falseCreator(false, "false?");

bool FunctionBoolQuery::is_valid(Element *element) {
	return Element::is_true(element) == _expected;
}
