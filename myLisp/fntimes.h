#if !defined(fntimes_h)
#define fntimes_h

	#include "listable.h"

	class FunctionTimes: public Listable {
	protected:
		virtual Ptr setup(State &callerState, bool &stop) override;

		virtual Ptr argument(Ptr intermediate, Ptr element, State &callerState, bool &stop) override;

		virtual Ptr empty_case(State &callerState) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (*) 1) "empty *")
	 *	(assert (= (* 2 3 4) 24) "* 2 3 4")
	 *	(assert (= (* 7) 7) "* 7")
	 *	(assert (= (* -3 5/2) -15/2) "fractional *")
	 *
	 *  (assert (= (* "2") (error "* expects numeric arguments")) "* string")
	 */

#endif
