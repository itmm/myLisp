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
	 *	(assert (= answer 42) "import")
	 */

	/*TESTS:
	 *
	 *	(assert (= (import 42) (error "string expected")) "import 42")
	 *	(assert (= (import "non-existent.lsp") (error "can't import non-existent.lsp")) "import non-existent")
	 */

#endif
