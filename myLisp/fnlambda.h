#if !defined(fnlambda_h)
#define fnlambda_h

	#include "function.h"

	class FunctionLambda: public Function {
        public:
            virtual EPtr apply(EPtr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (= (fn () (+ 3 3)) ()) false) "simple fn")
	 *	(assert (= ((fn () 3)) 3) "constant fn")
	 *	(assert (= (cond (((fn () false)) 2) (true 3)) 3) "fn in cond")
	 */

	/*TESTS:
	 *
	 *+	((fn macro () (def "a" 3)))
	 *
	 *	(assert (= a 3) "macro defines to global")
	 */

	/*TESTS:
	 *
	 *+ (def "a" (fn macro ("b") b))
	 *+	(a (def "x" 32))
	 *
	 *	(assert (= x 32) "indirect macro")
	 */

	/*TESTS:
	 *
	 *+ (def "f" (fn "args" (car args)))
	 *
	 *	(assert (= (f 2 3) 2) "simple global fn")
	 */

	/*TESTS:
	 *
	 *+ (def "f" (fn ("a" . "b") (+ a (car b))))
	 *
	 *	(assert (= (f 2 3 4) 5) "simple variadic fn")
	 */

	/*TESTS:
	 *
	 *	(assert (= (fn) (error "arguments expected")) "empty fn")
	 *	(assert (= (fn macro) (error "arguments expected")) "empty fn macro")
	 */

#endif
