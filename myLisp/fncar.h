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
	 *> #include "number.h"
	 *
	 *+	Parser p;
	 *
	 *	p.eval("(car (list 1 2))")->as_number()->value() == 1
	 *	p.eval("(car ())") == nullptr
	 *
	 *	p.eval("(car)") == p.creator()->new_error("car needs one argument")
	 *	p.eval("(car . 2)") == p.creator()->new_error("arguments of car are not a list")
	 *	p.eval("(car 2)") == p.creator()->new_error("car's argument must be a pair")
	 *	p.eval("(car (list 1 2) (list))") == p.creator()->new_error("car has more than one argument")
	 *
	 */

#endif
