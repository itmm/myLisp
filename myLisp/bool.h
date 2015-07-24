#if !defined(bool_h)
#define bool_h

	#include "number.h"

	class Bool: public Number {
		private:
			Bool(const Fractional &value): Number(value) {}

			friend class RootFactory;

	public:
		virtual void to_stream(std::ostream &output, bool escape) const override;
	};

/*TESTS:
 *
 *	(assert (= (str-print true) "true") "true")
 *	(assert (= (str-print false) "false") "false")
 *
 *	(assert (= (dictionary? true) false) "dictionary? true")
 *	(assert (= (error? true) false) "error? true")
 *	(assert (= (function? true) false) "function? true")
 *	(assert (= (identifier? true) false) "identifier? true")
 *	(assert (= (number? true) true) "number? true")
 *  (assert (= (pair? true) false) "pair? true")
 *  (assert (= (string? true) false) "string? true")
 *
 *	(assert (= (dictionary? false) false) "dictionary? false")
 *	(assert (= (error? false) false) "error? false")
 *	(assert (= (function? false) false) "function? false")
 *	(assert (= (identifier? false) false) "identifier? false")
 *	(assert (= (number? false) true) "number? false")
 *  (assert (= (pair? false) false) "pair? false")
 *  (assert (= (string? false) false) "string? false")
 */

#endif
