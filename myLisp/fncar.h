#if !defined(fncar_h)
#define fncar_h

	#include "function.h"

	class FunctionCar: public Function {
		public:
	private:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (car (list 1 2)) 1) "car list")
	 *	(assert (= (car (list)) (list)) "car ()")
	 *
	 *	(assert (= (car 2) (error "car's argument must be a pair")) "car 2")
	 *	(assert (= (car . 2) (error "arguments of car are not a list")) "car . 2")
	 *	(assert (= (car 2) (error "car's argument must be a pair")) "car 2")
	 *	(assert (= (car (list (1 2)) (list)) (error "car has more than one argument")) "car multiple")
	 *
	 * 	(assert (= (car (list 2 . 3)) 2) "= car")
	 */

#endif
