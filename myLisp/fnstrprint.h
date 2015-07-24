#if !defined(fnstrprint_h)
#define fnstrprint_h

	#include "function.h"

	class FunctionStrPrint: public Function {
	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (str-print) "") "empty str-print")
	 *	(assert (= (str-print false) "false") "str-print false")
	 *	(assert (= (str-print 1 2 3) "1 2 3") "str-print 1 2 3")
	 *	(assert (= (str-print "1" "2" "3") "1 2 3") "str-print \"1\" \"2\" \"3\"")
	 *	(assert (= (str-print unused-identifier) "unused-identifier") "str-print identifier")
	 */

#endif
