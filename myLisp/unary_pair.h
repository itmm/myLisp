#if ! defined(unary_pair_h)
#define unary_pair_h

#include "unary.h"

	class UnaryPairFunction : public UnaryFunction {
		protected:
			virtual Ptr apply_unary_pair(Ptr pair, State &state) = 0;

			virtual Ptr apply_unary(Ptr arg, State &callerState) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (car 2) (error "argument must be a pair")) "car 2")
	 */

#endif
