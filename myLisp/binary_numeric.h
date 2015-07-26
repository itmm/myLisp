#if ! defined(binary_numeric_h)
#define binary_numeric_h

	#include "binary.h"

	class BinaryNumericFunction : public BinaryFunction {
		protected:
			virtual Ptr apply_binary(const Fractional &first, const Fractional &second, State &state) = 0;

		virtual Ptr apply_binary(Ptr first, Ptr second, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (remainder "2" 1) (error "first argument not numeric")) "numeric binary str 1")
	 *	(assert (= (remainder 2 "1") (error "second argument not numeric")) "numeric binary 2 str")
	 */

#endif
