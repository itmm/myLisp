#if ! defined(expander_h)
#define expander_h

	#include "rewriter.h"

	class Expander : public Rewriter {
		public:
			Expander(Ptr replacements): _replacements(replacements) {}

		private:
			Ptr _replacements;
	public:
		virtual Ptr rewrite_identifier(Ptr identifier, Creator &creator) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (expand (dict ("a" 1) ("b" 2)) (a (b a))) (list 1 (2 1))) "expander")
	 */

#endif
