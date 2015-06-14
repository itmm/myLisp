#if !defined(fnplus_h)
#define fnplus_h

	#include "function.h"

	class FunctionPlus: public Function {
		public:
			virtual Ptr apply(Ptr arguments, Creator *creator) override;
	};

	/*TESTS:
	 *
	 *>	#include "number.h"
	 *
	 *	EVAL("(+)")->as_number()->value() == 0
	 *	EVAL("(+ 2 3 4)")->as_number()->value() == 9
	 *	EVAL("(+ 7)")->as_number()->value() == 7
	 *	EVAL("(+ -3 5/2)")->as_number()->value() == -Fractional(1, 2)
	 *
	 */

#endif
