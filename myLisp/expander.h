#if ! defined(expander_h)
#define expander_h

	#include "rewriter.h"

	class Expander : public Rewriter {
		public:
			Expander(EPtr replacements): _replacements(replacements) {}

		private:
			EPtr _replacements;
	public:
		virtual EPtr rewrite_identifier(EPtr identifier, Creator &creator) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (expand (dict ("a" 1) ("b" 2)) (a (b a))) (list 1 (2 1))) "expander")
	 */

#endif
