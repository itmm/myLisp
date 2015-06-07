#if !defined(fnplus_h)
#define fnplus_h

	#include "function.h"

	class FunctionPlus: public Function {
		public:
			virtual Element *apply(Element *arguments) override;
	};

	/*TESTS:
	 *
	 *>	#include "parser.h"
	 *>	#include "number.h"
	 *
	 *> static Fractional evalPlus(const std::string &source) {
	 *>		Collector collector;
	 *>		FunctionPlus *function = new FunctionPlus();
	 *>		Parser parser(&collector);
	 *>		Element *rest = parser.parse(source);
	 *>		Pair *arguments = collector.new_pair(function, rest);
	 *>		Number *result = function->apply(arguments)->as_number();
	 *> 	return result->value();
	 *> }
	 *
	 *	evalPlus("()") == 0
	 *	evalPlus("(2 3 4)") == 9
	 *	evalPlus("(7)") == 7
	 *	evalPlus("(-3 5/2)") == -Fractional(1, 2)
	 *
	 */

#endif
