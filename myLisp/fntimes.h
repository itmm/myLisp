#if !defined(fntimes_h)
#define fntimes_h

	#include "function.h"

	class FunctionTimes: public Function {
	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *>	#include "number.h"
	 *
	 *+ Parser p;
	 *
	 *	p.eval("(*)")->as_number()->value() == 1
	 *	p.eval("(* 2 3 4)")->as_number()->value() == 24
	 *	p.eval("(* 7)")->as_number()->value() == 7
	 *	p.eval("(* -3 5/2)")->as_number()->value() == -Fractional(15, 2)
	 *
	 */
#endif
