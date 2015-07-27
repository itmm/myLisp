#if ! defined(unary_pair_h)
#define unary_pair_h

#include "unary.h"

	class UnaryPairFunction : public UnaryFunction {
		protected:
			virtual EPtr apply_unary_pair(EPtr pair, State &state) = 0;

			virtual EPtr apply_unary(EPtr arg, State &callerState) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (car 2) (error "argument must be a pair")) "car 2")
	 */

#endif
