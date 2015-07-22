#if ! defined(fnapply_h)
#define fnapply_h

	#include "function.h"

	class FunctionApply: public Function {
	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (apply + (2 3 4)) 9) "apply")
	 */

#endif
