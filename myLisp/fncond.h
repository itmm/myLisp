#if !defined(fncond_h)
#define fncond_h

	#include "function.h"

	class FunctionCond : public Function {
		public:
			virtual EPtr apply(EPtr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (cond) (error "unmatched cond")) "empty cond")
	 *	(assert (= (cond 2) (error "entries must be pairs")) "cond 2")
	 *	(assert (= (cond ((+ 1 1) (+ 2 2)) (true false)) 4) "calculated cond")
	 *	(assert (= (cond (false 1) (false 2) (true 3)) 3) "third cond")
	 */

#endif
