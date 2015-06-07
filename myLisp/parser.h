#if !defined(parser_h)
#define parser_h

    #include <iostream>
    #include <string>

    #include "collector.h"
    #include "dictionary.h"
    #include "element.h"

    class Number;
    class Pair;
    class String;

    class Parser {
        public:
            Parser();
			Parser(Collector *collector);
            ~Parser();
            
            Element *parse(std::istream &source);
            Element *parse(const std::string &source);
        
        private:
            Parser(const Parser &) = delete;
            Parser &operator=(const Parser &) = delete;
        
            Collector *_collector;
            bool _localCollector;
        
            Dictionary *_context;
            bool _localContext;
            
            void eatSpace(std::istream::int_type &ch, std::istream &rest);
            Element *parseElement(std::istream::int_type &ch, std::istream &rest);
            Number *parseNumber(std::istream::int_type &ch, std::istream &rest);
            Pair *parsePair(std::istream::int_type &ch, std::istream &rest);
            String *parseString(std::istream::int_type &ch, std::istream &rest);
            Element *parseIdentifier(std::istream::int_type &ch, std::istream &rest);
    };

    inline Parser::Parser():
        _collector(new Collector()), _localCollector(true),
        _context(_collector->root_dictionary()), _localContext(true)
    {
        _collector->make_root(_context);
    }

	inline Parser::Parser(Collector *collector):
		_collector(collector), _localCollector(false),
		_context(_collector->root_dictionary()), _localContext(true)
	{
		_collector->make_root(_context);
	}

	inline Parser::~Parser() {
        if (_localContext) { _collector->release_root(_context); _context = nullptr; }
        if (_localCollector) { delete _collector; }
    }

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
     *  Parser().parse("Infinity")->as_number()->value() == Fractional::infinity()
     *  Parser().parse("abc") == nullptr
     *
     */

#endif
