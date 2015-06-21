#if !defined(parser_h)
#define parser_h

    #include <iostream>
    #include <string>

    #include "creator.h"
    #include "dictionary.h"
    #include "element.h"
	#include "ptr.h"
	#include "root_factory.h"
    #include "state.h"

    class Parser {
        public:
            Parser();
			Parser(State *state);
            ~Parser();

			Creator *creator() { return _state->creator(); }

            Ptr parse(std::istream &source);
            Ptr parse(const std::string &source);

        	Ptr eval(std::istream &source);
			Ptr eval(const std::string &source);

        private:
            Parser(const Parser &) = delete;
            Parser &operator=(const Parser &) = delete;
        
            State *_state;
            bool _local_state;
        
            void eatSpace(std::istream::int_type &ch, std::istream &rest);
            Ptr parseElement(std::istream::int_type &ch, std::istream &rest);
            Ptr parseNumber(std::istream::int_type &ch, std::istream &rest, bool negative);
            Ptr parsePair(std::istream::int_type &ch, std::istream &rest);
            Ptr parseString(std::istream::int_type &ch, std::istream &rest);
            Ptr parseIdentifier(std::istream::int_type first, std::istream::int_type &ch, std::istream &rest);
    };

    inline Parser::Parser():
        _state(new State()), _local_state(true)
    {}

	inline Parser::Parser(State *state):
		_state(state), _local_state(false)
	{
	}

	inline Parser::~Parser() {
        if (_local_state) { delete _state; }
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
     *  Parser().parse("()") == nullptr
     *
     *  Parser().eval("Infinity")->as_number()->value() == Fractional::infinity()
     *  Parser().parse("abc")->as_identifier() != nullptr
     *
     *	Parser().parse(";; some comments\n12")->as_number()->value() == 12
     *	Parser().parse(";;; 12\r13")->as_number()->value() == 13
     *	Parser().parse(";;") == nullptr
     *
     *+ OutSink os;
     *
     *  (os << Parser().parse("(2 3 4)")) == "(2 3 4)"
     *  (os << Parser().parse("(2 (3 4) ((5)))")) == "(2 (3 4) ((5)))"
     *  (os << Parser().parse("(2 . 3)")) == "(2 . 3)"
     *  (os << Parser().parse("(+)")) == "(+)"
     *
     */

#endif
