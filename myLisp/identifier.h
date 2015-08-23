#if !defined(identifier_h)
#define identifier_h

	#include "string.h"

	class Identifier : public String {
		public:
			virtual bool is_equal(Element *other) const override;

			virtual Identifier *as_identifier() override;
			virtual String *as_string() override;

            virtual void to_stream(std::ostream &stream, bool escape) const override;

		private:
			friend class Creator;

			Identifier(const std::string &str): String(str) {}
	};

	/*TESTS:
	 *
	 *	(assert (= (true? unknown-identifier) true))
	 *
	 *	(assert (= (dictionary? unknown-identifier) false))
	 *	(assert (= (error? unknown-identifier) false))
	 *	(assert (= (function? unknown-identifier) false))
	 *	(assert (= (identifier? unknown-identifier) true))
	 *	(assert (= (number? unknown-identifier) false))
	 *  (assert (= (pair? unknown-identifier) false))
	 *  (assert (= (string? unknown-identifier) false))
	 *
	 *  (assert (= (str-print (a)) "(a)"))
	 */
#endif
