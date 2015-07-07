#if !defined(fnequal_h)
#define fnequal_h

	#include "lookbehind.h"

	class FunctionEqual: public Lookbehind {
	protected:
		virtual bool is_valid(Element *last, Element *current) override;
	};

	/*TESTS:
	 *
	 * 	(= (= (list) (list)) true)
	 *	(= (= (list) (list 4)) false)
	 *
	 *	(= (=) (error "Listable needs at least one argument"))
	 *	(= (= (+ 1)) (error "Lookbehind needs at least two arguments"))
	 *	(= (= 0) (error "Lookbehind needs at least two arguments"))
	 *	(= (= 2 4/2) true)
	 *	(= (= 2 3) false)
	 *	(= (= "abc" "abc") true)
	 *	(= (= "aBc" "abc") false)
	 *	(= (= " a" "a") false)
	 *	(= (= "a " "a") false)
	 *	(= (= "1" 1) false)
	 *	(= (= (+ 2 2) (+ 3 1) (+ 4 0) (+ 5 -1)) true)
	 *	(= (= (list (1 2) 3 4) (list (1 2) 3 (+ 2 2))) true)
	 *	(= (= (list) (list)) true)
	 */

#endif
