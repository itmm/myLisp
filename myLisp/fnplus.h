#if !defined(fnplus_h)
#define fnplus_h

	#include "function.h"

	class FunctionPlus: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *>	#include "number.h"
	 *
	 *+ Parser p;
	 *
	 *	p.eval("(+)")->as_number()->value() == 0
	 *	p.eval("(+ 2 3 4)")->as_number()->value() == 9
	 *	p.eval("(+ 7)")->as_number()->value() == 7
	 *	p.eval("(+ -3 5/2)")->as_number()->value() == -Fractional(1, 2)
	 *
	 */

#endif
