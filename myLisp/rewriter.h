#if ! defined(rewriter_h)
#define rewriter_h

	#include "creator.h"

	class Rewriter {
		public:
			Rewriter() {}
			virtual ~Rewriter();

			virtual Ptr rewrite(Ptr element, Creator &creator);
			virtual Ptr rewrite_dictionary(Ptr dictionary, Creator &creator);
			virtual Ptr rewrite_error(Ptr error, Creator &creator);
			virtual Ptr rewrite_function(Ptr function, Creator &creator);
			virtual Ptr rewrite_identifier(Ptr identifier, Creator &creator);
			virtual Ptr rewrite_number(Ptr number, Creator &creator);
			virtual Ptr rewrite_pair(Ptr pair, Creator &creator);
			virtual Ptr rewrite_string(Ptr str, Creator &creator);

		private:
			Rewriter(const Rewriter &) = delete;
			Rewriter &operator=(const Rewriter &) = delete;
	};

#endif
