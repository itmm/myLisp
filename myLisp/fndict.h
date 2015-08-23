#if ! defined(fndict_h)
#define fndict_h

	#include "function.h"

	class FunctionDict : public Function {
	public:
		virtual EPtr apply(EPtr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (dict 3) (error "pair expected")))
	 *	(assert (= (dict (1 2 3)) (error "pair must have two elements")))
	 *	(assert (= (dict (1 2)) (error "key must be a string")))
	 *
	 *	(assert (= (dict) (dict)))
	 *	(assert (= (dict ("a" 1) ("b" 2)) (dict ("b" 2) ("a" 1))))
	 *	(assert (= (= (dict) (dict ("a" 1))) false))
	 */

#endif
