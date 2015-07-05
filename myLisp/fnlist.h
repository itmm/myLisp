#if !defined(fnlist_h)
#define fnlist_h

	#include "function.h"

	class FunctionList: public Function {
	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*LISP-TESTS:
	 *
	 * (= (list) (list))
	 * (= (list 1 2 3) (list 1 2 3))
	 * (= (list (+ 1 2) (+ 2 3)) (list 3 5))
	 */

#endif
