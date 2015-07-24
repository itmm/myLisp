#if ! defined(fnremainder_h)
#define fnremainder_h

	#include "numeric_binary.h"

	class FunctionRemainder : public NumericBinaryFunction {
	protected:
		virtual Ptr apply_binary(const Fractional &first, const Fractional &second, State &stateq) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (remainder 2 1) 0) "remainder 2 1")
	 *	(assert (= (remainder 10 7) 3) "remainder 10 7")
	 *	(assert (= (remainder -10 7) 3) "remainder -10 7")
	 *	(assert (= (remainder 10 -7) 3) "remainder 10 -7")
	 *	(assert (= (remainder -10 -7) 3) "remainder -10 -7")
	 *
	 *	(assert (= (remainder 2/3 1) (error "first argument must be integer")) "remainder 2/3 1")
	 *	(assert (= (remainder 2 1/2) (error "second argument must be integer")) "remainder 2/3 1")
	 */
#endif
