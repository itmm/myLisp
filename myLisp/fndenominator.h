#if ! defined(fndenominator_h)
#define fndenominator_h

#include "unary_numeric.h"

	class FunctionDenominator : public UnaryNumericFunction {
	protected:
		virtual EPtr apply_unary_numeric(const Fractional &value, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (denominator 0) 1) "denominator 0")
	 *	(assert (= (denominator 1) 1) "denominator 1")
	 *	(assert (= (denominator 7) 1) "denominator 7")
	 *	(assert (= (denominator -2/3) 3) "denominator -2/3")
	 *	(assert (= (denominator infinity) 0) "denominator infinity")
	 *	(assert (= (denominator (- infinity)) 0) "denominator -infinity")
	 *	(assert (= (denominator not-a-number) 0) "denominator not a number")
	 */

#endif
