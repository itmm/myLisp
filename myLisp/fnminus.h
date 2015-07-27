#if !defined(fnminus_h)
#define fnminus_h

	#include "listable_numeric.h"

	class FunctionMinus : public ListableNumericFunction {
		protected:
			virtual EPtr empty_case(State &callerState) override;

			virtual EPtr first_argument_numeric(
                EPtr intermediate,
                const Fractional &element,
                bool hasMore,
                State &callerState,
                bool &stop
            ) override;

			virtual EPtr argument_numeric(
                EPtr intermediate,
                const Fractional &element,
                State &callerState,
                bool &stop
            ) override;
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
     */

#endif
