#if ! defined(fnand_h)
#define fnand_h

	#include "listable.h"

	class FunctionAnd: public Listable {
		protected:
		virtual Ptr empty_case(State &callerState) override;

		virtual Ptr setup(State &callerState, bool &stop) override;

		virtual Ptr argument(Ptr intermediate, Element *element, State &callerState, bool &stop) override;
	};

	/*TESTS:
	 *
	 *	(= (and) true)
	 *
	 *	(= (and true) true)
	 *	(= (and 1) true)
	 *	(= (and false) false)
	 *	(= (and 0) 0)
	 *
	 *  (= (and false false) false)
	 *  (= (and false true) false)
	 *  (= (and true false) false)
	 *  (= (and true 1) true)
	 *
	 *  (= (and 1 2 3 4) true)
	 */

#endif