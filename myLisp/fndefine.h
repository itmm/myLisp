#if !defined(fndefine_h)
#define fndefine_h

	#include "function.h"

	class FunctionDefine : public Function {
		public:
			virtual EPtr apply(EPtr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (def "a" 3) 3))
	 */

	/*TESTS:
	 *
	 *+	(def "a" 42)
	 *	(assert (= (+ a a) 84))
	 */

	/*TESTS:
	 *
	 *	(assert (= (def) (error "arguments must be a list")))
	 *	(assert (= (def 2) (error "first argument must eval to string")))
	 *	(assert (= (def "a") (error "second argument needed")))
	 *	(assert (= (def "a" 2 3) (error "only two arguments expected")))
	 */

    /*TESTS:
     *
     *+ (def "a" nil)
     *  (assert (= a nil))
     */
     
#endif
