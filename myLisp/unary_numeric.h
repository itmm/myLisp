#if ! defined(unary_numeric_h)
#define unary_numeric_h

	#include "unary.h"

	class UnaryNumericFunction : public UnaryFunction {
		protected:
			virtual EPtr apply_unary_numeric(const Fractional &value, State &state) = 0;

			virtual EPtr apply_unary(EPtr arg, State &callerState) override;
	};

	/*TESTS:
	 *
	 *  (assert (= (denominator "1") (error "argument must be a number")))
	 */

#endif
