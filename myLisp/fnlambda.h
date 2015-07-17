#if !defined(fnlambda_h)
#define fnlambda_h

	#include "function.h"

	class FunctionLambda: public Function {
	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(= (= (fn () (+ 3 3)) ()) false)
	 *	(= ((fn () 3)) 3)
	 *	(= (cond (((fn () false)) 2) (true 3)) 3)
	 */

	/*TESTS:
	 *
	 *+	((fn macro () (def "a" 3)))
	 *
	 *	(= a 3)
	 */

	/*TESTS:
	 *
	 *+ (def "a" (fn macro ("b") (eval b)))
	 *+	(a (def "x" 32))
	 *
	 *	(= x 32)
	 */

	/*TESTS:
	 *
	 *+ (def "f" (fn "args" (car args)))
	 *
	 *	(= (f 2 3) 2)
	 */

	/*TESTS:
	 *
	 *+ (def "f" (fn ("a" . "b") (+ a (car b))))
	 *
	 *	(= (f 2 3 4) 5)
	 */
#endif
