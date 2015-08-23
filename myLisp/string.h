#if !defined(string_h)
#define string_h

    #include <string>

    #include "element.h"

    class String : public Element {
        public:

            const std::string &str() const { return _str; }

			virtual bool is_true() const override;
			virtual bool is_equal(Element *other) const override;
            virtual bool is_less(Element *other) const override;

			virtual String *as_string();
            virtual void to_stream(std::ostream &stream, bool escape) const override;

			friend class Creator;

		protected:
			String(const std::string &str): _str(str) {}

		private:
            std::string _str;
    };

	/*TESTS:
	 *
	 *	(assert (= (true? "") false))
	 *	(assert (= (true? " ") true))
	 *	(assert (= (true? "0") true))
	 *
	 *  (assert (= (= "ab" "ab") true))
	 *
	 *  (assert (= (< "abc" "aca") true))
	 *  (assert (= (< "A" "a") true))
	 *  (assert (= (< "" "a") true))
	 *  (assert (= (< "zz" "zza") true))
	 *  (assert (= (< "b" "b ") true))
	 *  (assert (= (< " b" "b") true))
	 *
	 *	(assert (= (dictionary? "dict") false))
	 *	(assert (= (error? "err") false))
	 *	(assert (= (function? "+") false))
	 *	(assert (= (identifier? "ab") false))
	 *	(assert (= (number? "0") false))
	 * 	(assert (= (pair? "()") false))
	 * 	(assert (= (string? "9") true))
	 * 	(assert (= (string? "") true))
	 *
	 *  (assert (= (str-print "x y") "x y"))
	 *  (assert (= (str-print "") ""))
	 */

#endif
