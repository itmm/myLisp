#include "parser.h"

#include <sstream>

EPtr Parser::parseNumber(const std::string &str) {
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
    return _state->creator()->new_number(Fractional(numerator, denominator, negative));
}

EPtr Parser::parseString(std::istream::int_type &ch, std::istream &rest) {
    ch = rest.get();
    std::ostringstream buffer;
    while (ch != EOF && ch != '"') {
    	if (ch == '\\') {
    		ch = rest.get();
    	}
        buffer << (char) ch;
        ch = rest.get();
    }
    if (ch == '"') { ch = rest.get(); }
    return _state->creator()->new_string(buffer.str());
}

void Parser::eatSpace(std::istream::int_type &ch, std::istream &rest) {
    while (ch != EOF && isspace(static_cast<int>(ch))) {
        ch = rest.get();
    }
}

EPtr Parser::parsePair(std::istream::int_type &ch, std::istream &rest) {
	if (ch == EOF) { return _state->error("unfinished list"); }
    if (ch == ')') {
        ch = rest.get();
        return EPtr();
    }
    EPtr car = parseElement(ch, rest);

    eatSpace(ch, rest);
    if (ch == '.') {
        ch = rest.get();
        EPtr cdr = parseElement(ch, rest);
        eatSpace(ch, rest);
        if (ch == ')') {
        	ch = rest.get();
        } else {
        	return _state->error("unfinished dotted list");
        }
        return _state->creator()->new_pair(car, cdr);
    } else {
        EPtr cdr = parsePair(ch, rest);
        return _state->creator()->new_pair(car, cdr);
    }
}

EPtr Parser::parseIdentifier(std::istream::int_type &ch, std::istream &rest) {
    std::ostringstream buffer;
    while (ch != EOF && !isspace(static_cast<int>(ch)) && ch != ')') {
        buffer << (char) ch;
        ch = rest.get();
    }
    const std::string &str = buffer.str();
    if (str.size() >= 2 && str[0] == ';' && str[1] == ';') {
    	// handle comments
    	while (ch != EOF && ch != '\n' && ch != '\r') {
			ch = rest.get();
		}
		return parseElement(ch, rest);
    }
    EPtr number = parseNumber(str);
    if (number) { return number; }
	return _state->creator()->new_identifier(str);
}

EPtr Parser::parseElement(std::istream::int_type &ch, std::istream &rest) {
	eatSpace(ch, rest);
	switch (ch) {
		case static_cast<std::istream::int_type>(EOF): return EPtr();
		case '\'': {
			ch = rest.get();
			EPtr quoted = parseElement(ch, rest);
			EPtr args = _state->creator()->new_pair(quoted, nullptr);
			return _state->creator()->new_pair(_state->root()->as_dictionary()->get("quote"), args);
		}
		case '"':
			return parseString(ch, rest);
		case '(':
			ch = rest.get();
			return parsePair(ch, rest);
		default:
			return parseIdentifier(ch, rest);
	}
}

EPtr Parser::parse(std::istream &source) {
	std::istream::int_type ch = source.get();
    return parseElement(ch, source);
}

EPtr Parser::parse(const std::string &source) {
    std::istringstream in(source);
    EPtr result = parse(in);
	return result;
}

EPtr Parser::eval(std::istream &source) {
	return _state->eval(parse(source));
}

EPtr Parser::eval(const std::string &source) {
	std::istringstream in(source);
	return eval(in);
}

