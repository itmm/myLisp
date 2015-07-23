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

	/*TESTS:
	 *
	 *	(assert (= (def) (error "arguments must be a list")) "empty def")
	 *	(assert (= (def 2) (error "first argument must eval to string")) "def 2")
	 *	(assert (= (def "a") (error "second argument needed")) "def a")
	 *	(assert (= (def "a" 2 3) (error "only two arguments expected")) "def a 2 3")
	 */

#endif
