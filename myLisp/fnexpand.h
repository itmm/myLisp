#if ! defined(fnexpand_h)
#define fnexpand_h

	#include "function.h"

	class FunctionExpand : public Function {
		public:
			virtual EPtr apply(EPtr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (expand (dict) 1) 1))
	 *
	 *	(assert (= (expand 1 2 3) (error "expand needs two arguments")))
	 *	(assert (= (expand 1 2) (error "first argument must be dictionary")))
	 */

#endif
