#if ! defined(integer_binary_h)
#define integer_binary_h

	#include "binary_numeric.h"

	class BinaryIntegerFunction : public BinaryNumericFunction {
		protected:
			virtual EPtr apply_binary(
                const Fractional &first,
                const Fractional &second,
                State &state
            ) override;
            
			virtual EPtr apply_integers(const BigInt &first, const BigInt &second, State &state) = 0;
	};

	/*TESTS:
	 *
	 *	(assert (= (remainder 2/3 1) (error "first argument must be integer")) "remainder 2/3 1")
	 *	(assert (= (remainder 2 1/2) (error "second argument must be integer")) "remainder 2/3 1")
	 */

#endif
