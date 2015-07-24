#if ! defined(fngcd_h)
#define fngcd_h

	#include "integer_binary.h"

	class FunctionGcd : public IntegerBinaryFunction {
		protected:
			virtual Ptr apply_integers(const BigInt &first, const BigInt &second, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (gcd 15 6) 3) "gcd 15 6")
	 *	(assert (= (gcd 6 15) 3) "gcd 6 15")
	 */

#endif
