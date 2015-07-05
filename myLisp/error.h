#if !defined(error_h)
#define error_h

	#include "string.h"

	class Error: public String {
		public:
			virtual bool is_true() const override;
			virtual bool is_equal(Element *other) const override;

			virtual Error *as_error() override;
			virtual String *as_string() override;

			virtual void to_stream(std::ostream &stream) const override;

		private:
			friend class Creator;

			Error(const std::string &message): String(message) {}
	};

	/*C++-TESTS:
	 *
	 *+	Creator c;
	 *
	 *	c.new_error("true")->is_true() == false
	 *
	 *  c.new_error("a")->as_dictionary() == nullptr
	 *  c.new_error("b")->as_error() != nullptr
	 *  c.new_error("c")->as_function() == nullptr
	 *  c.new_error("d")->as_identifier() == nullptr
	 *  c.new_error("e")->as_number() == nullptr
	 *  c.new_error("f")->as_pair() == nullptr
	 *  c.new_error("e")->as_string() == nullptr
	 *
	 *	(c.new_error("a") == c.new_error("a")) == true
	 *	(c.new_error("a") == c.new_error("b")) == false
	 *	(c.new_error("a") == c.new_string("a")) == false
	 *	(c.new_error("a") == c.new_identifier("a")) == false
	 */

	/*TESTS:
	 *
	 *	(= (str-print (error "not yet")) "(error \"not yet\")"
	 */

#endif
