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
	 *	(assert (= (str-print (error "not yet")) "(error \"not yet\")") "str-print error")
	 *
	 *	(assert (= (true? (error "true")) false) "true? error")
	 *
	 *	(assert (= (dictionary? (error "[]")) false) "dictionary? error")
	 *	(assert (= (error? (error "err")) true) "error? error")
	 *  (assert (= (function? (error "+")) false) "function? error")
	 *  (assert (= (identifier? (error "abc")) false) "identifier? error")
	 *	(assert (= (number? (error "2")) false) "number? error")
	 *  (assert (= (pair? (error "()")) false) "pair? error")
	 *  (assert (= (string? (error "abc")) false) "string? error")
	 *
	 *  (assert (= (= (error "a") (error "a")) true) "= error a a")
	 *  (assert (= (= (error "a") (error "b")) false) "= error a b")
	 *  (assert (= (= (error "a") "a") false) "= error string")
	 *  (assert (= (= (error "unused-identifier") unused-identifier) false) "= error identifier")
	 */

#endif
