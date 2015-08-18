#if ! defined(token_h)
#define token_h

    #include <string>
//    #include <iostream>

    typedef enum {
        kTokenUnknown,
        kTokenEof,
        kTokenWhitespace,
        kTokenComment,
        kTokenLeftParenthesis,
        kTokenRightParenthesis,
        kTokenIdentifier,
        kTokenNumber,
        kTokenString,
        kTokenQuote,
        kTokenDot
    } TokenType;

    class Token {
        public:
            Token(TokenType type, size_t begin, const std::string &value);
        
            TokenType type() const { return _type; }
            size_t begin() const { return _begin; }
            size_t end() const { return _begin + _value.size(); }
            const std::string &value() const { return _value; }
            int level() const { return _level; }
        
            void set_level(int level) { _level = level; }
        
        private:
            TokenType _type;
            size_t _begin;
            std::string _value;
            int _level;
    };

    inline Token::Token(TokenType type, size_t begin, const std::string &value):
        _type(type),
        _begin(begin),
        _value(value),
        _level(0)
    {
//        std::cerr << "parsing ";
//        switch (_type) {
//            case kTokenUnknown: std::cerr << "??"; break;
//            case kTokenEof: std::cerr << "EOF"; break;
//            case kTokenWhitespace: std::cerr << "ws"; break;
//            case kTokenComment: std::cerr << ";;"; break;
//            case kTokenLeftParenthesis: std::cerr << "("; break;
//            case kTokenRightParenthesis: std::cerr << ")"; break;
//            case kTokenIdentifier: std::cerr << "id"; break;
//            case kTokenNumber: std::cerr << "##"; break;
//            case kTokenString: std::cerr << "\""; break;
//            case kTokenQuote: std::cerr << "'"; break;
//            case kTokenDot: std::cerr << "."; break;
//            default: std::cerr << "????"; break;
//            
//        }
//        std::cerr << " @" << _begin;
//        std::cerr << ": " << _value << std::endl;
    }

#endif
