#if !defined(fnerror_h)
#define fnerror_h

	#include "function.h"

	class FunctionError: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *+ Parser p;
	 *+ OutSink os;
	 *
	 *	(os << p.eval("(error \"test\")")) == "(error \"test\")"
	 *
	 *  (os << p.eval("(error)")) == "(error \"error must have one argument\")"
	 *  (os << p.eval("(error . 2)")) == "(error \"error arguments must be a list\")"
	 *  (os << p.eval("(error \"a\" \"b\")")) == "(error \"error has more than one argument\")"
	 *  (os << p.eval("(error 2)")) == "(error \"error argument must be a string\")"
	 *
	 */

#endif
