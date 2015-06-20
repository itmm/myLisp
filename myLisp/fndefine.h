#if !defined(fndefine_h)
#define fndefine_h

	#include "function.h"

	class FunctionDefine: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

    /*TESTS:
     *
     *> #include "number.h"
     *
     *+ Parser p;
     *+ p.eval("(def \"a\" 42)");
     *
     *	p.eval("(+ a a)")->as_number()->value() == 84
     *
     */

    /*TESTS:
     *
     *+ Parser p;
     *
     *  p.eval("(def \"a\" 3)")->as_number()->value() == 3
     *
     */

#endif
