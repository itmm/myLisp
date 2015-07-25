#if ! defined(unary_numeric_h)
#define unary_numeric_h

	#include "unary.h"

	class UnaryNumericFunction : public UnaryFunction {
		protected:
			virtual Ptr apply_unary_numeric(const Fractional &value, State &state) = 0;

			virtual Ptr apply_unary(Ptr arg, State &callerState) override;
	};

	/*TESTS:
	 *
	 *  (assert (= (denominator "1") (error "argument must be a number")) "unary numeric string")
	 */

#endif
