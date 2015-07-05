#if !defined(fndefine_h)
#define fndefine_h

	#include "function.h"

	class FunctionDefine: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(= (def a 3) 3)
	 */

	/*TESTS:
	 *
	 *+	(def a 42)
	 *	(= (+ a a) 84)
	 */

#endif
