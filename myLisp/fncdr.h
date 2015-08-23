#if !defined(fncdr_h)
#define fncdr_h

	#include "unary_pair.h"

	class FunctionCdr : public UnaryPairFunction {
		protected:
			virtual EPtr apply_unary_pair(EPtr pair, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (cdr (list)) (list)))
	 *	(assert (= (cdr (list 1 2)) (list 2)))
	 *
	 * 	(assert (= (cdr (list 2 . (4 5))) (list 4 5)))
	 */

#endif
