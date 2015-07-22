#if !defined(fncdr_h)
#define fncdr_h

	#include "function.h"

	class FunctionCdr: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (cdr (list)) (list)) "cdr ()")
	 *	(assert (= (cdr (list 1 2)) (list 2)) "cdr list")
	 *
	 *  (assert (= (cdr) (error "cdr needs one argument")) "empty cdr")
	 *  (assert (= (cdr . 2) (error "arguments of cdr are not a list")) "cdr . 2")
	 *  (assert (= (cdr 2) (error "cdr's argument must be a pair")) "cdr 2")
	 *  (assert (= (cdr (list 1 2) (list)) (error "cdr has more than one argument")) "cdr multiple")
	 *
	 * 	(assert (= (cdr (list 2 . (4 5))) (list 4 5)) "cdr no-list")
	 */

#endif
