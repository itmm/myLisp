#if !defined(fncar_h)
#define fncar_h

	#include "unary_pair.h"

	class FunctionCar : public UnaryPairFunction {
		protected:
			virtual EPtr apply_unary_pair(EPtr pair, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (car (1 2)) 1))
	 *	(assert (= (car ()) ()))
	 *
	 * 	(assert (= (car (2 . 3)) 2))
	 */

#endif
