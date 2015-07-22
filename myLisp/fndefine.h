#if !defined(fndefine_h)
#define fndefine_h

	#include "function.h"

	class FunctionDefine: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (def "a" 3) 3) "define")
	 */

	/*TESTS:
	 *
	 *+	(def "a" 42)
	 *	(assert (= (+ a a) 84) "check defined")
	 */

#endif
