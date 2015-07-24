#if !defined(fnplus_h)
#define fnplus_h

	#include "listable.h"

	class FunctionPlus: public Listable {
	protected:
		virtual Ptr empty_case(State &callerState) override;

		virtual Ptr setup(State &callerState, bool &stop) override;

		virtual Ptr argument(Ptr intermediate, Ptr element, State &callerState, bool &stop) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (+) 0) "empty +")
	 *	(assert (= (+ 2 3 4) 9) "multiple +")
	 *	(assert (= (+ 7) 7) "+ 7")
	 *	(assert (= (+ -3 5/2) -1/2) "fractional +")
	 *
	 *  (assert (= (+ . 2) (error "Listable needs a plain list")) "+ . 2")
	 *  (assert (= (+ 1 . 2) (error "Listable needs a plain list")) "+ 1 . 2")
	 *  (assert (= (+ 1 "a") (error "+ expects numeric arguments")) "mixed plus")
	 */

#endif
