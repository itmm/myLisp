#if !defined(fnplus_h)
#define fnplus_h

	#include "function.h"

	class FunctionPlus: public Function {
		public:
			virtual Ptr apply(Ptr arguments, Creator *creator) override;
	};

	/*TESTS:
	 *
	 *>	#include "parser.h"
	 *>	#include "number.h"
	 *
	 *> static Fractional evalPlus(const std::string &source) {
	 *>		Creator creator;
	 *>		FunctionPlus *function = new FunctionPlus();
	 *>		Parser parser(&creator);
	 *>		Ptr rest = parser.parse(source);
	 *>		Ptr arguments = creator.new_pair(function, rest);
	 *>		Number *result = function->apply(arguments, &creator)->as_number();
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
