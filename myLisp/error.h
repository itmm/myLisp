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

	/*TESTS:
	 *
	 *	(= (str-print (error "not yet")) "(error \"not yet\")")
	 *
	 *	(= (true? (error "true")) false)
	 *
	 *	(= (dictionary? (error "[]")) false)
	 *	(= (error? (error "err")) true)
	 *  (= (function? (error "+")) false)
	 *  (= (identifier? (error "abc")) false)
	 *	(= (number? (error "2")) false)
	 *  (= (pair? (error "()")) false)
	 *  (= (string? (error "abc")) false)
	 *
	 *  (= (= (error "a") (error "a")) true)
	 *  (= (= (error "a") (error "b")) false)
	 *  (= (= (error "a") "a") false)
	 *  (= (= (error "unused-identifier") unused-identifier) false)
	 */

#endif