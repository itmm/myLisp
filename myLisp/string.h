#if !defined(string_h)
#define string_h

    #include <string>

    #include "element.h"

    class String: public Element {
        public:

            const std::string &str() const { return _str; }

			virtual bool is_true() const override;
			virtual bool is_equal(Element *other) const override;

			virtual String *as_string();
            virtual void to_stream(std::ostream &stream) const;

			friend class Creator;

		protected:
			String(const std::string &str): _str(str) {}

		private:
            std::string _str;
	};

    /*C++-TESTS:
     *
     *+ Creator c;
     *
     *  c.new_string("**")->as_function() == nullptr
     *  c.new_string("[]")->as_dictionary() == nullptr
     *  c.new_string("abc")->as_identifier() == nullptr
     */

	/*TESTS:
	 *
	 *	(= (true? "") false)
	 *	(= (true? " ") true)
	 *	(= (true? "0") true)
	 *
	 *	(= (number? "0") false)
	 * 	(= (pair? "()") false)
	 * 	(= (string? "9") true)
	 * 	(= (string? "") true)
	 *
	 *  (= (str-print "x y") "x y")
	 *  (= (str-print "") "")
	 */

#endif
