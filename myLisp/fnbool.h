#if !defined(fnbool_h)
#define fnbool_h

	#include "function.h"

	class FunctionBool: public Function {
		public:
			FunctionBool(bool expected): _expected(expected) {}

			virtual Ptr apply(Ptr arguments, State &state) override;

		private:
			bool _expected;
	};

	/*LISP-TESTS:
	 *
	 *	(= (true? true) true)
	 *	(= (true? false) false)
	 *	(= (false? true) false)
	 *	(= (false? false) true)
	 *
	 *  (= (true? 1 2 "ab") true)
	 *  (= (false? 0 "") true)
	 */

#endif
