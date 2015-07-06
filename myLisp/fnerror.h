#if !defined(fnerror_h)
#define fnerror_h

	#include "function.h"

	class FunctionError: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(= (error "test") (error "test"))
	 *
	 *	(= (error) (error "error must have one argument"))
	 *	(= (error . 2) (error "error arguments must be a list"))
	 *	(= (error "a" "b") (error "error has more than one argument"))
	 *	(= (error 2) (error "error argument must be a string"))
	 *
	 */

#endif
