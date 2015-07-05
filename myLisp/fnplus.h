#if !defined(fnplus_h)
#define fnplus_h

	#include "function.h"

	class FunctionPlus: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(= (+) 0)
	 *	(= (+ 2 3 4) 9)
	 *	(= (+ 7) 7)
	 *	(= (+ -3 5/2) -1/2)
	 *
	 *  (= (+ . 2) (error "+ expects argument list"))
	 *  (= (+ 1 . 2) (error "+ expects argument list"))
	 *  (= (+ 1 "a") (error "+ expects numeric arguments"))
	 */

#endif
