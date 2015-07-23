#if ! defined(numerator_h)
#define numerator_h

	#include "function.h"

	class FunctionNumerator: public Function {
	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (numerator 0) 0) "numerator 0")
	 *	(assert (= (numerator 3) 3) "numerator 3")
	 *	(assert (= (numerator 2/5) 2) "numerator 2/5")
	 *	(assert (= (numerator 6/3) 2) "numerator 6/3")
	 *
	 *  (assert (= (numerator) (error "argument must be numeric")) "empty numerator")
	 *  (assert (= (numerator "1") (error "argument must be numeric")) "numerator string")
	 *  (assert (= (numerator 1 2) (error "too many arguments")) "numerator 1 2")
	 */
#endif
