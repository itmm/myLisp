#if ! defined(fndict_h)
#define fndict_h

	#include "function.h"

	class FunctionDict : public Function {
	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (dict 3) (error "pair expected")) "dict number")
	 *	(assert (= (dict (1 2 3)) (error "pair must have two elements")) "dict triple number")
	 *	(assert (= (dict (1 2)) (error "key must be a string")) "dict no-string pair")
	 *
	 *	(assert (= (dict) (dict)) "dict = empty")
	 *	(assert (= (dict ("a" 1) ("b" 2)) (dict ("b" 2) ("a" 1))) "dict = same")
	 *	(assert (= (= (dict) (dict ("a" 1))) false) "dict = not empty")
	 */

#endif
