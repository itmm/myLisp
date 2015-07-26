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
            Ptr parseNumber(const std::string &str);
            Ptr parsePair(std::istream::int_type &ch, std::istream &rest);
            Ptr parseString(std::istream::int_type &ch, std::istream &rest);
            Ptr parseIdentifier(std::istream::int_type &ch, std::istream &rest);
    };

    inline Parser::Parser():
        _state(new State()), _local_state(true)
    {
    	_state->setName("parser-local");
    }

	inline Parser::Parser(State *state):
		_state(state), _local_state(false)
	{
	}

	inline Parser::~Parser() {
        if (_local_state) { delete _state; }
    }

	/*TESTS:
	 *
	 *	(assert (= (str-print (2 3 4)) "(2 3 4)") "str-print (2 3 4)")
	 *	(assert (= (str-print (2 (3 4) ((5)))) "(2 (3 4) ((5)))") "str-print (2 (3 4) ((5)))")
	 *	(assert (= (str-print (2 . 3)) "(2 . 3)") "str-print (2 . 3)")
	 *
	 *  (assert (identifier? 'unknown) "single quote quote")
	 */

#endif
