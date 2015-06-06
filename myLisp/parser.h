#if !defined(parser_h)
#define parser_h

    #include <iostream>
    #include <string>

    #include "collector.h"
    #include "element.h"

    class Number;
    class Pair;
    class String;

    class Parser {
        public:
            Parser(): _collector(new Collector()), _localCollector(true) {}
            ~Parser() { if (_localCollector) { delete _collector; } }
            
            Element *parse(std::istream &source);
            Element *parse(const std::string &source);
        
        private:
            Parser(const Parser &);
            Parser &operator=(const Parser &);
        
            Collector *_collector;
            bool _localCollector;
        
            void eatSpace(int &ch, std::istream &rest);
            Element *parseElement(int &ch, std::istream &rest);
            Number *parseNumber(int &ch, std::istream &rest);
            Pair *parsePair(int &ch, std::istream &rest);
            String *parseString(int &ch, std::istream &rest);
    };

    /*TESTS:
     *
     *> #include "number.h"
     *> #include "pair.h"
     *> #include "string.h"
     *
     *  Parser().parse("") == nullptr
     *  Parser().parse(" \t\n\r") == nullptr
     *
     *  Parser().parse("3")->as_number()->value() == 3
     *  Parser().parse("  2/3")->as_number()->value() == Fractional(2, 3)
     *  Parser().parse("-2/3")->as_number()->value() == -Fractional(2, 3)
     *
     *  Parser().parse("\n\"abc\"")->as_string()->str() == "abc"
     *
     *  Parser().parse("()") == Pair::null()
     *  (OUT << *Parser().parse("(2 3 4)")) == "(2 3 4)"
     *  (OUT << *Parser().parse("(2 (3 4) ((5)))")) == "(2 (3 4) ((5)))"
     *  (OUT << *Parser().parse("(2 . 3)")) == "(2 . 3)"
     *
     */

#endif
