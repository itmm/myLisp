#if !defined(fnminus_h)
#define fnminus_h

	#include "listable.h"

	class FunctionMinus: public Listable {
		protected:
			virtual Ptr empty_case(State &callerState) override;

			virtual Ptr first_argument(Ptr intermediate, Element *element, bool hasMore, State &callerState, bool &stop) override;

			virtual Ptr argument(Ptr intermediate, Element *element, State &callerState, bool &stop) override;
	};

	/*	Some strange behavior was added: (-) returns -1 and (- a) returns -a.
	 *	So - can be used as an unary operator and (+), (-) can be used to mark
	 *	different states as 0 and -1.
	 */

    /*TESTS:
     *
     *  (= (-) -1)
     *  (= (- 1/3) -1/3)
     *  (= (- 10 2 3) 5)
     *  (= (- -3) 3)
     *  (= (- 1/3 2) -5/3)
     *
     *  (= (- "2") (error "- expects numeric arguments")
     *  (= (- 4 "2") (error "- expects numeric arguments")
     */

#endif
