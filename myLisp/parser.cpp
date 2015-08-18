#include "parser.h"

#include "tokenizer.h"

#include <sstream>

EPtr Parser::parseNumber(Tokenizer &tokenizer) {
    auto str = tokenizer.cur().value();
    BigInt numerator = 0;
    BigInt denominator;
    bool negative = false;

    auto cur = str.begin();
    auto end = str.end();

    if (cur != end && *cur == '-') { negative = true; ++cur; }

	if (cur == end || !isnumber(*cur)) { return EPtr(); }
	for (; cur != end && isnumber(*cur); ++cur) {
        numerator = numerator * BigInt(10) + BigInt(*cur - '0');
	}
	if (cur != end) {
		if (*cur != '/') { return EPtr(); }
		++cur;
		if (cur == end || !isnumber(*cur)) { return EPtr(); }
		denominator = 0;
		for (; cur != end && isnumber(*cur); ++cur) {
    	    denominator = denominator * BigInt(10) + BigInt(*cur - '0');
		}
		if (cur != end) { return EPtr(); }
	} else {
		denominator = 1;
	}
    EPtr res = _state->creator()->new_number(Fractional(numerator, denominator, negative));
    tokenizer.next();
    return res;
}

EPtr Parser::parseString(Tokenizer &tokenizer) {
    auto str = tokenizer.cur().value();
    auto i = str.begin();
    auto e = str.end();

    std::ostringstream buffer;
    ++i;
    while (i != e && *i != '"') {
    	if (*i == '\\') {
            ++i;
    	}
        if (i == e) break;
        buffer << *i;
        ++i;
    }
    if (i == e) return _state->error("incomplete string");
    EPtr result = _state->creator()->new_string(buffer.str());
    tokenizer.next();
    return result;
}

void Parser::eatSpace(Tokenizer &tokenizer) {
    while (tokenizer.cur().type() == kTokenComment || tokenizer.cur().type() == kTokenWhitespace) {
        tokenizer.next();
    }
}

EPtr Parser::parsePair(Tokenizer &tokenizer) {
    eatSpace(tokenizer);
	if (tokenizer.cur().type() == kTokenEof) { return _state->error("unfinished list"); }
    if (tokenizer.cur().type() == kTokenRightParenthesis) {
        tokenizer.next();
        return EPtr();
    }
    EPtr car = parseElement(tokenizer);

    eatSpace(tokenizer);
    if (tokenizer.cur().type() == kTokenDot) {
        tokenizer.next();
        EPtr cdr = parseElement(tokenizer);
        eatSpace(tokenizer);
        if (tokenizer.cur().type() == kTokenRightParenthesis) {
        	tokenizer.next();
        } else {
        	return _state->error("unfinished dotted list");
        }
        return _state->creator()->new_pair(car, cdr);
    } else {
        EPtr cdr = parsePair(tokenizer);
        return _state->creator()->new_pair(car, cdr);
    }
}

EPtr Parser::parseIdentifier(Tokenizer &tokenizer) {
    EPtr result = _state->creator()->new_identifier(tokenizer.cur().value());
    tokenizer.next();
    return result;
}

EPtr Parser::parseElement(Tokenizer &tokenizer) {
    eatSpace(tokenizer);
	switch (tokenizer.cur().type()) {
		case kTokenQuote: {
            tokenizer.next();
			EPtr quoted = parseElement(tokenizer);
			EPtr args = _state->creator()->new_pair(quoted, nullptr);
			return _state->creator()->new_pair(_state->root()->as_dictionary()->get("quote"), args);
		}
		case kTokenString:
			return parseString(tokenizer);
		case kTokenLeftParenthesis:
			tokenizer.next();
			return parsePair(tokenizer);
        case kTokenIdentifier:
            return parseIdentifier(tokenizer);
        case kTokenNumber:
            return parseNumber(tokenizer);
		default:
            return EPtr();
	}
}

EPtr Parser::parse(Tokenizer &tokenizer) {
    return parseElement(tokenizer);
}

EPtr Parser::parse(const std::string &source) {
    std::istringstream in(source);
    Tokenizer tokenizer(in);
    EPtr result = parse(tokenizer);
	return result;
}

EPtr Parser::eval(Tokenizer &tokenizer) {
	return _state->eval(parse(tokenizer));
}

EPtr Parser::eval(const std::string &source) {
	std::istringstream in(source);
    Tokenizer tokenizer(in);
	return eval(tokenizer);
}

