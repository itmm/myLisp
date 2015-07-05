#if !defined(fnplus_h)
#define fnplus_h

	#include "listable.h"

	class FunctionPlus: public Listable {
	protected:
		virtual Ptr empty_case(State &callerState) override;

		virtual Ptr setup(State &callerState, bool &stop) override;

		virtual Ptr argument(Ptr intermediate, Element *element, State &callerState, bool &stop) override;
	};

	/*TESTS:
	 *
	 *	(= (+) 0)
	 *	(= (+ 2 3 4) 9)
	 *	(= (+ 7) 7)
	 *	(= (+ -3 5/2) -1/2)
	 *
	 *  (= (+ . 2) (error "Listable needs a plain list"))
	 *  (= (+ 1 . 2) (error "Listable needs a plain list"))
	 *  (= (+ 1 "a") (error "+ expects numeric arguments"))
	 */

#endif
