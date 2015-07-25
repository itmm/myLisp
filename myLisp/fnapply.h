#if ! defined(fnapply_h)
#define fnapply_h

	#include "binary.h"

	class FunctionApply: public BinaryFunction {
		protected:
			virtual Ptr apply_binary(Ptr first, Ptr second, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (apply + (2 3 4)) 9) "apply")
	 */

#endif
