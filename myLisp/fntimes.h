#if !defined(fntimes_h)
#define fntimes_h

	#include "listable_numeric.h"

	class FunctionTimes : public ListableNumericFunction {
        protected:
            virtual EPtr setup(State &callerState, bool &stop) override;

            virtual EPtr argument_numeric(
                EPtr intermediate,
                const Fractional &element,
                State &callerState,
                bool &stop
            ) override;

            virtual EPtr empty_case(State &callerState) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (*) 1))
	 *	(assert (= (* 2 3 4) 24))
	 *	(assert (= (* 7) 7))
	 *	(assert (= (* -3 5/2) -15/2))
	 */

#endif
