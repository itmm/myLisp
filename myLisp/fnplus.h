#if !defined(fnplus_h)
#define fnplus_h

	#include "listable_numeric.h"

	class FunctionPlus : public ListableNumericFunction {
	protected:
		virtual EPtr empty_case(State &callerState) override;

		virtual EPtr setup(State &callerState, bool &stop) override;

		virtual EPtr argument_numeric(
            EPtr intermediate,
            const Fractional &element,
            State &callerState,
            bool &stop
        ) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (+) 0))
	 *	(assert (= (+ 2 3 4) 9))
	 *	(assert (= (+ 7) 7))
	 *	(assert (= (+ -3 5/2) -1/2))
	 */

#endif
