#if !defined(fnequal_h)
#define fnequal_h

	#include "function.h"

	class FunctionEqual: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *+ Parser p;
	 *
	 * 	p.eval("(=)")->is_true() == false
	 * 	p.eval("(= (+ 1))")->is_true() == false
	 * 	p.eval("(= 0)")->is_true() == true
	 *	p.eval("(= 2 4/2)")->is_true() == true
	 * 	p.eval("(= 2 3)")->is_true() == false
	 *
	 */
#endif
