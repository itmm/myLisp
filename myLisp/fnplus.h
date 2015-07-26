#if !defined(fnplus_h)
#define fnplus_h

	#include "listable_numeric.h"

	class FunctionPlus : public ListableNumericFunction {
	protected:
		virtual Ptr empty_case(State &callerState) override;

		virtual Ptr setup(State &callerState, bool &stop) override;

		virtual Ptr argument_numeric(
            Ptr intermediate,
            const Fractional &element,
            State &callerState,
            bool &stop
        ) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (+) 0) "empty +")
	 *	(assert (= (+ 2 3 4) 9) "multiple +")
	 *	(assert (= (+ 7) 7) "+ 7")
	 *	(assert (= (+ -3 5/2) -1/2) "fractional +")
	 */

#endif
