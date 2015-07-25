#if !defined(unary_h)
#define unary_h

	#include "function.h"

	class UnaryFunction : public Function {
		protected:
			virtual Ptr apply_unary(Ptr arg, State &callerState) = 0;

		public:
			virtual Ptr apply_evaled(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (car) (error "need one argument")) "car")
	 *	(assert (= (car . 2) (error "need one argument")) "car . 2")
	 *	(assert (= (car ((1 2)) ()) (error "too many arguments")) "car multiple")
	 */

#endif
