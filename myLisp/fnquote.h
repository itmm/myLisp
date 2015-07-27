#if !defined(fnquote_h)
#define fnquote_h

	#include "function.h"

	class FunctionQuote: public Function {
	public:
		virtual EPtr apply(EPtr arguments, State &state) override;
	};

	/*TESTS:
	 *
	 *	(assert (identifier? (quote +)) "quote +")
	 */

#endif
