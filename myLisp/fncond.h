#if !defined(fncond_h)
#define fncond_h

	#include "function.h"

	class FunctionCond: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(= (cond) (list))
	 *	(= (cond (+ 1 1) (+ 2 2) true false) 4)
	 *	(= (cond false 1 false 2 true 3) 3)
	 */

#endif
