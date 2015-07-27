#if ! defined(rewriter_h)
#define rewriter_h

	#include "creator.h"

	class Rewriter {
		public:
			Rewriter() {}
			virtual ~Rewriter();

			virtual EPtr rewrite(EPtr element, Creator &creator);
			virtual EPtr rewrite_dictionary(EPtr dictionary, Creator &creator);
			virtual EPtr rewrite_error(EPtr error, Creator &creator);
			virtual EPtr rewrite_function(EPtr function, Creator &creator);
			virtual EPtr rewrite_identifier(EPtr identifier, Creator &creator);
			virtual EPtr rewrite_number(EPtr number, Creator &creator);
			virtual EPtr rewrite_pair(EPtr pair, Creator &creator);
			virtual EPtr rewrite_string(EPtr str, Creator &creator);

		private:
			Rewriter(const Rewriter &) = delete;
			Rewriter &operator=(const Rewriter &) = delete;
	};

#endif
