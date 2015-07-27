#if ! defined(binary_h)
#define binary_h

	#include "function.h"

	class BinaryFunction : public Function {
		protected:
			virtual EPtr apply_binary(EPtr first, EPtr second, State &state) = 0;

		public:
			virtual EPtr apply_evaled(EPtr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (remainder) (error "no first argument")) "empty binary")
	 *	(assert (= (remainder . 2) (error "no first argument")) "binary . 2")
	 *	(assert (= (remainder 2) (error "no second argument")) "unary binary")
	 *	(assert (= (remainder 2 . 1) (error "no second argument")) "binary 2 . 1")
	 *	(assert (= (remainder 2 1 0) (error "more than two arguments")) "binary 2 1 0")
	 *	(assert (= (remainder 2 1 . 0) (error "more than two arguments")) "binary 2 1 . 0")
	 */

#endif
