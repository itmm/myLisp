#if ! defined(binary_numeric_h)
#define binary_numeric_h

	#include "binary.h"

	class BinaryNumericFunction : public BinaryFunction {
		protected:
			virtual EPtr apply_binary(const Fractional &first, const Fractional &second, State &state) = 0;

            virtual EPtr apply_binary(EPtr first, EPtr second, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (remainder "2" 1) (error "first argument not numeric")))
	 *	(assert (= (remainder 2 "1") (error "second argument not numeric")))
	 */

#endif
