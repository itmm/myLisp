#if !defined(fnquote_h)
#define fnquote_h

	#include "function.h"

	class FunctionQuote: public Function {
	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (identifier? (quote +)) "quote +")
	 */

#endif
