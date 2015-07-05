#if !defined(fntimes_h)
#define fntimes_h

	#include "function.h"

	class FunctionTimes: public Function {
	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*LISP-TESTS:
	 *
	 *	(= (*) 1)
	 *	(= (* 2 3 4) 24)
	 *	(= (* 7) 7)
	 *	(= (* -3 5/2) -15/2)
	 */

#endif
