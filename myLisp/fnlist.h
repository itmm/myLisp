#if !defined(fnlist_h)
#define fnlist_h

	#include "function.h"

	class FunctionList : public Function {
        public:
            virtual EPtr apply_evaled(EPtr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 * (assert (= (list) (list)))
	 * (assert (= (list 1 2 3) (list 1 2 3)))
	 * (assert (= (list (+ 1 2) (+ 2 3)) (list 3 5)))
	 */

#endif
