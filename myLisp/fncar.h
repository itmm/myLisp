#if !defined(fncar_h)
#define fncar_h

	#include "unary_pair.h"

	class FunctionCar : public UnaryPairFunction {
		protected:
			virtual Ptr apply_unary_pair(Ptr pair, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (car (1 2)) 1) "car list")
	 *	(assert (= (car ()) ()) "car ()")
	 *
	 * 	(assert (= (car (2 . 3)) 2) "= car")
	 */

#endif
