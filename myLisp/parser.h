#if !defined(parser_h)
#define parser_h

    #include <iostream>
    #include <string>

    #include "creator.h"
    #include "dictionary.h"
    #include "element.h"
	#include "ptr.h"

    class Parser {
        public:
            Parser();
			Parser(Creator *creator);
            ~Parser();

			Creator *creator() { return _creator; }
			Collector *collector() { return _creator->collector(); }

            Ptr parse(std::istream &source);
            Ptr parse(const std::string &source);
        
        private:
            Parser(const Parser &) = delete;
            Parser &operator=(const Parser &) = delete;
        
            Creator *_creator;
            bool _local_creator;
        
            Ptr _context;

            void eatSpace(std::istream::int_type &ch, std::istream &rest);
            Ptr parseElement(std::istream::int_type &ch, std::istream &rest);
            Ptr parseNumber(std::istream::int_type &ch, std::istream &rest);
            Ptr parsePair(std::istream::int_type &ch, std::istream &rest);
            Ptr parseString(std::istream::int_type &ch, std::istream &rest);
            Ptr parseIdentifier(std::istream::int_type &ch, std::istream &rest);
    };

    inline Parser::Parser():
        _creator(new Creator()), _local_creator(true),
        _context(_creator->collector()->root_dictionary(), _creator->collector())
    {}

	inline Parser::Parser(Creator *creator):
		_creator(creator), _local_creator(false),
		_context(_creator->collector()->root_dictionary(), _creator->collector())
	{
	}

	inline Parser::~Parser() {
		_context = Ptr(nullptr, _creator->collector());
        if (_local_creator) { delete _creator; _creator = nullptr; }
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
