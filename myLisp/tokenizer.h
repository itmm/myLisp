#if ! defined(tokenizer_h)
#define tokenizer_h

    #include "token.h"

    #include <iostream>
    #include <sstream>

    class Tokenizer {
        public:
            Tokenizer(std::istream &in): _in(in), _pos(0), _ch(_in.get()), _token(kTokenUnknown, 0, std::string()) {
                next();
            }
        
            Token &cur() { return _token; }
            Token &next();
        
        private:
            std::istream &_in;
            size_t _pos;
            std::istream::int_type _ch;
            Token _token;
        
            void read();
            std::string single_value();
        
            Token &whitespace();
            Token &string();
            Token &comment(size_t begin, std::ostringstream &buffer);
            bool is_number(const std::string &str);
            Token &identifier();
    };

#endif
