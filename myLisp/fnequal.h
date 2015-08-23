#if !defined(fnequal_h)
#define fnequal_h

	#include "lookbehind.h"

	class FunctionEqual : public Lookbehind {
        protected:
            virtual bool is_valid(Element *last, Element *current) override;
	};

	/*TESTS:
	 *
	 * 	(assert (= (= (list) (list)) true))
	 *	(assert (= (= (list) (list 4)) false))
	 *
	 *	(assert (= (=) (error "Listable needs at least one argument")))
	 *	(assert (= (= (+ 1)) (error "Lookbehind needs at least two arguments")))
	 *	(assert (= (= 2 4/2) true))
	 *	(assert (= (= 2 3) false))
	 *	(assert (= (= "abc" "abc") true))
	 *	(assert (= (= "aBc" "abc") false))
	 *	(assert (= (= " a" "a") false))
	 *	(assert (= (= "a " "a") false))
	 *	(assert (= (= "1" 1) false))
	 *	(assert (= (= (+ 2 2) (+ 3 1) (+ 4 0) (+ 5 -1)) true))
	 *	(assert (= (= (list (1 2) 3 4) (list (1 2) 3 (+ 2 2))) true))
	 *	(assert (= (= (list) (list)) true))
	 */

#endif
