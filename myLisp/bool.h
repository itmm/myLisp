#if !defined(bool_h)
#define bool_h

	#include "number.h"

	class Bool : public Number {
		private:
			Bool(const Fractional &value): Number(value) {}

			friend class RootFactory;

        public:
            virtual void to_stream(std::ostream &output, bool escape) const override;
	};

    /*TESTS:
     *
     *	(assert (= (str-print true) "true"))
     *	(assert (= (str-print false) "false"))
     *
     *	(assert (= (dictionary? true) false))
     *	(assert (= (error? true) false))
     *	(assert (= (function? true) false))
     *	(assert (= (identifier? true) false))
     *	(assert (= (number? true) true))
     *  (assert (= (pair? true) false))
     *  (assert (= (string? true) false))
     *
     *	(assert (= (dictionary? false) false))
     *	(assert (= (error? false) false))
     *	(assert (= (function? false) false))
     *	(assert (= (identifier? false) false))
     *	(assert (= (number? false) true))
     *  (assert (= (pair? false) false))
     *  (assert (= (string? false) false))
     */

#endif
