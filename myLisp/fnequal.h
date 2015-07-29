#if !defined(fnequal_h)
#define fnequal_h

	#include "lookbehind.h"

	class FunctionEqual : public Lookbehind {
        protected:
            virtual bool is_valid(Element *last, Element *current) override;
	};

	/*TESTS:
	 *
	 * 	(assert (= (= (list) (list)) true) "= empty lists")
	 *	(assert (= (= (list) (list 4)) false) "= unequal lists")
	 *
	 *	(assert (= (=) (error "Listable needs at least one argument")) "empty =")
	 *	(assert (= (= (+ 1)) (error "Lookbehind needs at least two arguments")) "= single")
	 *	(assert (= (= 2 4/2) true) "= equal numbers")
	 *	(assert (= (= 2 3) false) "= unequal numbers")
	 *	(assert (= (= "abc" "abc") true) "= equal strings")
	 *	(assert (= (= "aBc" "abc") false) "= unequal strings")
	 *	(assert (= (= " a" "a") false) "= strings with spaces in front")
	 *	(assert (= (= "a " "a") false) "= strings with spaces in rear")
	 *	(assert (= (= "1" 1) false) "= string with number")
	 *	(assert (= (= (+ 2 2) (+ 3 1) (+ 4 0) (+ 5 -1)) true) "= list of numbers")
	 *	(assert (= (= (list (1 2) 3 4) (list (1 2) 3 (+ 2 2))) true) "= with lists")
	 *	(assert (= (= (list) (list)) true) "= with ()")
	 */

#endif
