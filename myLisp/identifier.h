#if !defined(identifier_h)
#define identifier_h

	#include "string.h"

	class Identifier: public String {
		public:
			virtual bool is_equal(Element *other) const override;

			virtual Identifier *as_identifier() override;
			virtual String *as_string() override;

		private:
			friend class Creator;

			Identifier(const std::string &str): String(str) {}
	};

	/*TESTS:
	 *
	 *	(= (true? unknown-identifier) true)
	 *
	 *	(= (number? unknown-identifier) false)
	 *  (= (pair? unknown-identifier) false)
	 *  (= (string? unknown-identifier) false)
	 */
#endif
