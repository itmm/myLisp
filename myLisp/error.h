#if !defined(error_h)
#define error_h

	#include "pair.h"

	class Error : public Pair {
		public:
			virtual bool is_true() const override;
			virtual bool is_equal(Element *other) const override;

			virtual Error *as_error() override;
			virtual Pair *as_pair() override;

        protected:
            virtual std::string head() const override;
            
		private:
			friend class Creator;

			Error(Element *head, Element *rest): Pair(head, rest) {}
	};

	/*TESTS:
	 *
	 *	(assert (= (str-print (error "not yet")) "(error \"not yet\")"))
	 *
	 *	(assert (= (true? (error "true")) false))
	 *
	 *	(assert (= (dictionary? (error "[]")) false))
	 *	(assert (= (error? (error "err")) true))
	 *  (assert (= (function? (error "+")) false))
	 *  (assert (= (identifier? (error "abc")) false))
	 *	(assert (= (number? (error "2")) false))
	 *  (assert (= (pair? (error "()")) false))
	 *  (assert (= (string? (error "abc")) false))
	 *
	 *  (assert (= (= (error "a") (error "a")) true))
	 *  (assert (= (= (error "a") (error "b")) false))
	 *  (assert (= (= (error "a") "a") false))
	 *  (assert (= (= (error "unused-identifier") unused-identifier) false))
	 */

#endif
