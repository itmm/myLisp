#if !defined(fncond_h)
#define fncond_h

	#include "function.h"

	class FunctionCond : public Function {
		public:
			virtual EPtr apply(EPtr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (cond) (error "unmatched cond")))
	 *	(assert (= (cond 2) (error "entries must be pairs")))
	 *	(assert (= (cond ((+ 1 1) (+ 2 2)) (true false)) 4))
	 *	(assert (= (cond (false 1) (false 2) (true 3)) 3))
	 */

#endif
