#if !defined(unary_h)
#define unary_h

	#include "function.h"

	class UnaryFunction : public Function {
		protected:
			virtual EPtr apply_unary(EPtr arg, State &callerState) = 0;

		public:
			virtual EPtr apply_evaled(EPtr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (car) (error "need one argument")) "car")
	 *	(assert (= (car . 2) (error "need one argument")) "car . 2")
	 *	(assert (= (car ((1 2)) ()) (error "too many arguments")) "car multiple")
	 */

#endif
