#if ! defined(fndenominator_h)
#define fndenominator_h

	#include "function.h"

	class FunctionDenominator : public Function {
	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
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
	 *
	 *  (assert (= (denominator) (error "argument must be numeric")) "empty denominator")
	 *  (assert (= (denominator "1") (error "argument must be numeric")) "denominator string")
	 *  (assert (= (denominator 1 2) (error "too many arguments")) "denominator 1 2")
	 */

#endif