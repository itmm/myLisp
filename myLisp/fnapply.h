#if ! defined(fnapply_h)
#define fnapply_h

	#include "function.h"

	class FunctionApply: public Function {
	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(= (apply + (2 3 4)) 9)
	 */

#endif
