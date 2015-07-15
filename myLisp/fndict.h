#if ! defined(fndict_h)
#define fndict_h

	#include "function.h"

	class FunctionDict : public Function {
	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(= (dict 3) (error "pair expected"))
	 *	(= (dict (1 2 3)) (error "pair must have two elements"))
	 *	(= (dict (1 2)) (error "key must be a string"))
	 *
	 *	(= (dict) (dict))
	 *	(= (dict ("a" 1) ("b" 2)) (dict ("b" 2) ("a" 1)))
	 *	(= (= (dict) (dict ("a" 1))) false)
	 */

#endif
