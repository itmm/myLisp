#if !defined(fncdr_h)
#define fncdr_h

	#include "function.h"

	class FunctionCdr: public Function {
	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *> #include "number.h"
	 *
	 *+	Parser p;
	 *
	 *	p.eval("(cdr)") == nullptr
	 *	p.eval("(cdr ())") == nullptr
	 *
	 *+ OutSink os;
	 *
	 *	(os << p.eval("(cdr (list 1 2))")) == "(2)"
	 */

#endif
