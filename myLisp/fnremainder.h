#if ! defined(fnremainder_h)
#define fnremainder_h

	#include "integer_binary.h"

	class FunctionRemainder : public IntegerBinaryFunction {
		protected:
			virtual Ptr apply_integers(const BigInt &first, const BigInt &second, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (remainder 2 1) 0) "remainder 2 1")
	 *	(assert (= (remainder 10 7) 3) "remainder 10 7")
	 *	(assert (= (remainder -10 7) 3) "remainder -10 7")
	 *	(assert (= (remainder 10 -7) 3) "remainder 10 -7")
	 *	(assert (= (remainder -10 -7) 3) "remainder -10 -7")
	 */

#endif
