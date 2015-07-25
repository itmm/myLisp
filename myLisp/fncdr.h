#if !defined(fncdr_h)
#define fncdr_h

	#include "unary_pair.h"

	class FunctionCdr : public UnaryPairFunction {
		protected:
			virtual Ptr apply_unary_pair(Ptr pair, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (cdr (list)) (list)) "cdr ()")
	 *	(assert (= (cdr (list 1 2)) (list 2)) "cdr list")
	 *
	 * 	(assert (= (cdr (list 2 . (4 5))) (list 4 5)) "cdr no-list")
	 */

#endif
