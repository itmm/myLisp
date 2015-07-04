#if !defined(fncdr_h)
#define fncdr_h

	#include "function.h"

	class FunctionCdr: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*LISP-TESTS:
	 *
	 *	(= (cdr ()) ())
	 *	(= (cdr (list 1 2)) (list 2))
	 *
	 *  (= (cdr) (error "cdr needs one argument"))
	 *  (= (cdr . 2) (error "arguments of cdr are not a list"))
	 *  (= (cdr 2) (error "cdr's argument must be a pair"))
	 *  (= (cdr (list 1 2) (list)) (error "cdr has more than one argument"))
	 *
	 * 	(= (cdr (list 2 . (4 5))) (list 4 5))
	 *
	 */

#endif
