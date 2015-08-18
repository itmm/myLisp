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

    class Tokenizer;

    class Parser {
        public:
            Parser();
			Parser(State *state);
            ~Parser();

			Creator *creator() { return _state->creator(); }

            EPtr parse(Tokenizer &tokenizer);
            EPtr parse(const std::string &source);

        	EPtr eval(Tokenizer &tokenizer);
			EPtr eval(const std::string &source);

        private:
            Parser(const Parser &) = delete;
            Parser &operator=(const Parser &) = delete;
        
            State *_state;
            bool _local_state;
        
            void eatSpace(Tokenizer &tokenizer);
            EPtr parseElement(Tokenizer &tokenizer);
            EPtr parseNumber(Tokenizer &tokenizer);
            EPtr parsePair(Tokenizer &tokenizer);
            EPtr parseString(Tokenizer &tokenizer);
            EPtr parseIdentifier(Tokenizer &tokenizer);
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
