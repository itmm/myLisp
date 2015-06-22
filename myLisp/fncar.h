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
	 *	p.eval("(car)") == nullptr
	 *	p.eval("(car ())") == nullptr
	 *
	 */

#endif
