#if !defined(string_h)
#define string_h

    #include <string>

    #include "element.h"

    class String: public Element {
        public:
            String(const std::string &str): _str(str) {}
        
            const std::string &str() { return _str; }
        
            virtual String *as_string();
            virtual void to_stream(std::ostream &stream) const;
    
        private:
            std::string _str;
    };

    /*TESTS:
     *
     *  String("[]").as_dictionary() == nullptr
     *  String("8").as_number() == nullptr
     *  String("(1 2)").as_pair() == nullptr
     *  String("9").as_string() != nullptr
     *  String("pv").as_string()->str() == "pv"
     * 
     *  String("abc").str() == "abc"
     *  (OUT << String("x y")) == "\"x y\""
     *  (OUT << String("")) == "\"\""
     *
     */
     
#endif
