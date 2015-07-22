#if !defined(fnerror_h)
#define fnerror_h

	#include "function.h"

	class FunctionError: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (error "test") (error "test")) "test error")
	 *
	 *	(assert (= (error) (error "error must have one argument")) "empty error")
	 *	(assert (= (error . 2) (error "error arguments must be a list")) "error . 2")
	 *	(assert (= (error "a" "b") (error "error has more than one argument")) "error a b")
	 *	(assert (= (error 2) (error "error argument must be a string")) "error 2")
	 */

#endif
