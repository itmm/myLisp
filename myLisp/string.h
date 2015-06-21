#if !defined(string_h)
#define string_h

    #include <string>

    #include "element.h"

    class String: public Element {
        public:

            const std::string &str() const { return _str; }

			virtual bool is_true() const override;

			virtual String *as_string();
            virtual void to_stream(std::ostream &stream) const;

			friend class Creator;

		protected:
			String(const std::string &str): _str(str) {}

		private:
            std::string _str;
	};

    /*TESTS:
     *
     *+ Creator c;
     *
     *	c.new_string("")->is_true() == false
     *	c.new_string(" ")->is_true() == true
     *	c.new_string("0")->is_true() == true
     *
     *  c.new_string("**")->as_function() == nullptr
     *  c.new_string("[]")->as_dictionary() == nullptr
     *  c.new_string("abc")->as_identifier() == nullptr
     *  c.new_string("8")->as_number() == nullptr
     *  c.new_string("1 2")->as_pair() == nullptr
     *  c.new_string("9")->as_string() != nullptr
     *  c.new_string("pv")->as_string()->str() == "pv"
     * 
     *  c.new_string("abc")->as_string()->str() == "abc"
     *
     *+ OutSink os;
     *
     *  (os << c.new_string("x y")) == "\"x y\""
     *  (os << c.new_string("")) == "\"\""
     *
     */
     
#endif
