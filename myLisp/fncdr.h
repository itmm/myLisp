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
	 *	p.eval("(cdr ())") == nullptr
	 *
	 *	p.eval("(cdr)") == p.creator()->new_error("cdr needs one argument")
	 *	p.eval("(cdr . 2)") == p.creator()->new_error("arguments of cdr are not a list")
	 *	p.eval("(cdr 2)") == p.creator()->new_error("cdr's argument must be a pair")
	 *	p.eval("(cdr (list 1 2) (list))") == p.creator()->new_error("cdr has more than one argument")
	 *
	 *+ OutSink os;
	 *
	 *	(os << p.eval("(cdr (list 1 2))")) == "(2)"
	 *
	 */

#endif
