#if !defined(fnplus_h)
#define fnplus_h

	#include "function.h"

	class FunctionPlus: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*LISP-TESTS:
	 *
	 *	(= (+) 0)
	 *	(= (+ 2 3 4) 9)
	 *	(= (+ 7) 7)
	 *	(= (+ -3 5/2) -1/2)
	 *
	 */

#endif
