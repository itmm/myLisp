#if !defined(identifier_h)
#define identifier_h

	#include "string.h"

	class Identifier: public String {
		public:
			virtual Identifier *as_identifier() override;
			virtual String *as_string() override;

			virtual void to_stream(std::ostream &stream) const override;

		private:
			friend class Creator;

			Identifier(const std::string &str): String(str) {}
	};


#endif
