#if !defined(fnstrprint_h)
#define fnstrprint_h

	#include "function.h"

	class FunctionStrPrint: public Function {
	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(= (str-print) "")
	 *	(= (str-print false) "false")
	 *	(= (str-print 1 2 3) "1 2 3")
	 *	(= (str-print unused-identifier) "unused-identifier")
	 */

#endif
