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
 *  (= (pair? true) false)
 *  (= (pair? false) false)
 */

#endif
