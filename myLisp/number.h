#ifndef number_h
#define number_h

    #include "element.h"
    #include "fractional.h"

    class Number : public Element {
        public:

            virtual Number *as_number();
            virtual void to_stream(std::ostream &output, bool escape) const override;
        
            const Fractional &value() const { return _value; }

			virtual bool is_true() const override;
			virtual bool is_equal(Element *other) const override;
            virtual bool is_less(Element *other) const override;

        protected:
			friend class Creator;

			Number(const Fractional &value): _value(value) {}

		private:
            Fractional _value;
	};

	/*TESTS:
	 *
	 *	(assert (= (true? 0) false))
	 *	(assert (= (true? 1) true))
	 *	(assert (= (true? -2/3) true))
	 *
	 *	(assert (= (dictionary? 0) false))
	 *	(assert (= (error? -1) false))
	 *	(assert (= (function? 2) false))
	 *	(assert (= (identifier? 3) false))
	 *	(assert (= (number? 0) true))
	 *	(assert (= (number? -2/3) true))
	 *	(assert (= (number? infinity) true))
	 *	(assert (= (number? (- infinity)) true))
	 *	(assert (= (number? not-a-number) true))
	 *	(assert (= (pair? 2) false))
	 *	(assert (= (string? 3) false))
	 *
	 *  (assert (= (str-print -2/3) "-2/3"))
	 */

#endif
