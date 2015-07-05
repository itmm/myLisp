#if !defined(fnimport_h)
#define fnimport_h

	#include "function.h"

	class FunctionImport: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *+	(= (import "simple.lsp") true)
	 *
	 *	(= answer 42)
	 *
	 */

#endif
