#if ! defined(fnexpand_h)
#define fnexpand_h

	#include "function.h"

	class FunctionExpand: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(= (expand (dict) 1) 1)
	 *
	 *	(= (expand 1 2 3) (error "expand needs two arguments"))
	 *	(= (expand 1 2) (error "first argument must be dictionary"))
	 */

#endif
