#if !defined(fnlist_h)
#define fnlist_h

	#include "function.h"

	class FunctionList: public Function {
	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *+	Parser p;
	 *+	OutSink os;
	 *
	 * (os << p.eval("(list)")) == "()"
	 * (os << p.eval("(list 1 2 3)")) == "(1 2 3)"
	 * (os << p.eval("(list (+ 1 2) (+ 2 3))")) == "(3 5)"
	 */

#endif
