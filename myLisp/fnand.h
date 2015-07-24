#if ! defined(fnand_h)
#define fnand_h

	#include "listable.h"

	class FunctionAnd: public Listable {
		protected:
		virtual Ptr empty_case(State &callerState) override;

		virtual Ptr setup(State &callerState, bool &stop) override;

		virtual Ptr argument(Ptr intermediate, Ptr element, State &callerState, bool &stop) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (and) true) "empty and")
	 *
	 *	(assert (= (and true) true) "and true")
	 *	(assert (= (and 1) true) "and 1")
	 *	(assert (= (and false) false) "and false")
	 *	(assert (= (and 0) 0) "and 0")
	 *
	 *  (assert (= (and false false) false) "and false false")
	 *  (assert (= (and false true) false) "and false true")
	 *  (assert (= (and true false) false) "and true false")
	 *  (assert (= (and true 1) true) "and true 1")
	 *
	 *  (assert (= (and 1 2 3 4) true) "and 1 2 3 4")
	 */

#endif