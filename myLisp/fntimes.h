#if !defined(fntimes_h)
#define fntimes_h

	#include "listable.h"

	class FunctionTimes: public Listable {
	protected:
		virtual Ptr setup(State &callerState, bool &stop) override;

		virtual Ptr argument(Ptr intermediate, Element *element, State &callerState, bool &stop) override;

		virtual Ptr empty_case(State &callerState) override;
	};

	/*TESTS:
	 *
	 *	(= (*) 1)
	 *	(= (* 2 3 4) 24)
	 *	(= (* 7) 7)
	 *	(= (* -3 5/2) -15/2)
	 *
	 *  (= (* "2") (error "* expects numeric arguments")
	 */

#endif
