#if !defined(bool_h)
#define bool_h

	#include "number.h"

	class Bool: public Number {
		private:
			Bool(const Fractional &value): Number(value) {}

			friend class RootFactory;

	public:
		virtual void to_stream(std::ostream &output) const override;
	};

/*TESTS:
 *
 *	(= (str-print true) "true")
 *	(= (str-print false) "false")
 *
 *	(= (number? true) true)
 *  (= (pair? true) false)
 *  (= (string? true) false)
 *
 *	(= (number? false) true)
 *  (= (pair? false) false)
 *  (= (string? false) false)
 */

#endif
