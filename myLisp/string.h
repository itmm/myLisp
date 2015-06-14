#if !defined(string_h)
#define string_h

    #include <string>

    #include "element.h"

    class String: public Element {
        public:

            const std::string &str() { return _str; }
        
            virtual String *as_string();
            virtual void to_stream(std::ostream &stream) const;

			friend class Creator;

        private:
			String(const std::string &str): _str(str) {}

            std::string _str;
    };

    /*TESTS:
     *
     *  STRING("**")->as_function() == nullptr
     *  STRING("[]")->as_dictionary() == nullptr
     *  STRING("8")->as_number() == nullptr
     *  STRING("1 2")->as_pair() == nullptr
     *  STRING("9")->as_string() != nullptr
     *  STRING("pv")->as_string()->str() == "pv"
     * 
     *  STRING("abc")->str() == "abc"
     *  (OUT << *STRING("x y")) == "\"x y\""
     *  (OUT << *STRING("")) == "\"\""
     *
     */
     
#endif
