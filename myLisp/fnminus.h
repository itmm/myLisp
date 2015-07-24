#if !defined(fnminus_h)
#define fnminus_h

	#include "listable.h"

	class FunctionMinus: public Listable {
		protected:
			virtual Ptr empty_case(State &callerState) override;

			virtual Ptr first_argument(Ptr intermediate, Ptr element, bool hasMore, State &callerState, bool &stop) override;

			virtual Ptr argument(Ptr intermediate, Ptr element, State &callerState, bool &stop) override;
	};

	/*	Some strange behavior was added: (-) returns -1 and (- a) returns -a.
	 *	So - can be used as an unary operator and (+), (-) can be used to mark
	 *	different states as 0 and -1.
	 */

    /*TESTS:
     *
     *  (assert (= (-) -1) "empty -")
     *  (assert (= (- 1/3) -1/3) "- 1/3")
     *  (assert (= (- 10 2 3) 5) "multiple -")
     *  (assert (= (- -3) 3) "- -3")
     *  (assert (= (- 1/3 2) -5/3) "- fractional")
     *
     *  (assert (= (- "2") (error "- expects numeric arguments")) "- string")
     *  (assert (= (- 4 "2") (error "- expects numeric arguments")) "- mixed arguments")
     */

#endif
