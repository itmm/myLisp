#if !defined(fncond_h)
#define fncond_h

	#include "function.h"

	class FunctionCond: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *>	#include "number.h"
	 *
	 *+ Parser p;
	 *
	 *	p.eval("(cond)") == nullptr
	 *	p.eval("(cond (+ 1 1) (+ 2 2) true false)")->as_number()->value() == 4
	 *	p.eval("(cond false 1 false 2 true 3)")->as_number()->value() ==3
	 *
	 */
#endif
