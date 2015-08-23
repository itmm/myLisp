#if ! defined(fndenominator_h)
#define fndenominator_h

#include "unary_numeric.h"

	class FunctionDenominator : public UnaryNumericFunction {
	protected:
		virtual EPtr apply_unary_numeric(const Fractional &value, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (denominator 0) 1))
	 *	(assert (= (denominator 1) 1))
	 *	(assert (= (denominator 7) 1))
	 *	(assert (= (denominator -2/3) 3))
	 *	(assert (= (denominator infinity) 0))
	 *	(assert (= (denominator (- infinity)) 0))
	 *	(assert (= (denominator not-a-number) 0))
	 */

#endif
