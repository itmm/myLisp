#if !defined(string_h)
#define string_h

    #include <string>

    #include "element.h"

    class String: public Element {
        public:
            String(const std::string &str): _str(str) {}
        
            const std::string &str() { return _str; }
        
            virtual String *to_string();
            virtual void to_stream(std::ostream &stream);
    
        private:
            std::string _str;
    };

#endif
