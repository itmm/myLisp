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
	 *	(assert (= (true? unknown-identifier) true) "true? identifier")
	 *
	 *	(assert (= (dictionary? unknown-identifier) false) "dictionary? identifier")
	 *	(assert (= (error? unknown-identifier) false) "error? identifier")
	 *	(assert (= (function? unknown-identifier) false) "function? identifier")
	 *	(assert (= (identifier? unknown-identifier) true) "identifier? identifier")
	 *	(assert (= (number? unknown-identifier) false) "number? identifier")
	 *  (assert (= (pair? unknown-identifier) false) "pair? identifier")
	 *  (assert (= (string? unknown-identifier) false) "string? identifier")
	 *
	 *  (assert (= (str-print (a)) "(a)") "str-print (a)")
	 */
#endif
