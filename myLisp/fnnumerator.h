#if ! defined(numerator_h)
#define numerator_h

	#include "unary_numeric.h"

	class FunctionNumerator : public UnaryNumericFunction {
		protected:
			virtual EPtr apply_unary_numeric(const Fractional &value, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (numerator 0) 0))
	 *	(assert (= (numerator 3) 3))
	 *	(assert (= (numerator 2/5) 2))
	 *	(assert (= (numerator 6/3) 2))
	 */

#endif
