#if !defined(fnequal_h)
#define fnequal_h

	#include "function.h"

	class FunctionEqual: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*LISP-TESTS:
	 *
	 * 	(= (= (list) (list)) true)
	 *	(= (= (list) (list 4)) false)
	 *
	 *	(= (=) false)
	 *	(= (= (+ 1)) false)
	 *	(= (= 0) true)
	 *	(= (= 2 4/2) true)
	 *	(= (= 2 3) false)
	 *	(= (= "abc" "abc") true)
	 *	(= (= "aBc" "abc") false)
	 *	(= (= " a" "a") false)
	 *	(= (= "a " "a") false)
	 *	(= (= "1" 1) false)
	 *	(= (= (+ 2 2) (+ 3 1) (+ 4 0)) true)
	 *	(= (= (list (1 2) 3 4) (list (1 2) 3 (+ 2 2))) true)
	 */

#endif
