#if !defined(fnlambda_h)
#define fnlambda_h

	#include "function.h"

	class FunctionLambda : public Function {
        public:
            virtual EPtr apply(EPtr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (= (fn () (+ 3 3)) ()) false))
	 *	(assert (= ((fn () 3)) 3))
	 *	(assert (= (cond (((fn () false)) 2) (true 3)) 3))
	 */

	/*TESTS:
	 *
	 *+	((fn macro () (def "a" 3)))
	 *
	 *	(assert (= a 3))
	 */

	/*TESTS:
	 *
	 *+ (def "a" (fn macro ("b") b))
	 *+	(a (def "x" 32))
	 *
	 *	(assert (= x 32))
	 */

	/*TESTS:
	 *
	 *+ (def "f" (fn "args" (car args)))
	 *
	 *	(assert (= (f 2 3) 2))
	 */

	/*TESTS:
	 *
	 *+ (def "f" (fn ("a" . "b") (+ a (car b))))
	 *
	 *	(assert (= (f 2 3 4) 5))
	 */

	/*TESTS:
	 *
	 *	(assert (= (fn) (error "arguments expected")))
	 *	(assert (= (fn macro) (error "arguments expected")))
	 */

#endif
