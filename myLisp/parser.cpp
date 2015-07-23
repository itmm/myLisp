#include "parser.h"

#include <sstream>

Ptr Parser::parseNumber(const std::string &str) {
    BigInt numerator = 0;
    BigInt denominator;
    bool negative = false;

    auto cur = str.begin();
    auto end = str.end();

    if (cur != end && *cur == '-') { negative = true; ++cur; }

	if (cur == end || !isnumber(*cur)) { return Ptr(); }
	for (; cur != end && isnumber(*cur); ++cur) {
        numerator = numerator * BigInt(10) + BigInt(*cur - '0');
	}
	if (cur != end) {
		if (*cur != '/') { return Ptr(); }
		++cur;
		if (cur == end || !isnumber(*cur)) { return Ptr(); }
		denominator = 0;
		for (; cur != end && isnumber(*cur); ++cur) {
    	    denominator = denominator * BigInt(10) + BigInt(*cur - '0');
		}
		if (cur != end) { return Ptr(); }
	} else {
		denominator = 1;
	}
    return _state->creator()->new_number(Fractional(numerator, denominator, negative));
}

Ptr Parser::parseString(std::istream::int_type &ch, std::istream &rest) {
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

Ptr Parser::parsePair(std::istream::int_type &ch, std::istream &rest) {
	if (ch == EOF) { return _state->creator()->new_error("unfinished list"); }
    if (ch == ')') {
        ch = rest.get();
        return Ptr();
    }
    Ptr car = parseElement(ch, rest);

    eatSpace(ch, rest);
    if (ch == '.') {
        ch = rest.get();
        Ptr cdr = parseElement(ch, rest);
        eatSpace(ch, rest);
        if (ch == ')') {
        	ch = rest.get();
        } else {
        	return _state->creator()->new_error("unfinished dotted list");
        }
        return _state->creator()->new_pair(car, cdr);
    } else {
        Ptr cdr = parsePair(ch, rest);
        return _state->creator()->new_pair(car, cdr);
    }
}

Ptr Parser::parseIdentifier(std::istream::int_type &ch, std::istream &rest) {
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
    Ptr number = parseNumber(str);
    if (number) { return number; }
	return _state->creator()->new_identifier(str);
}

Ptr Parser::parseElement(std::istream::int_type &ch, std::istream &rest) {
	eatSpace(ch, rest);
	switch (ch) {
		case static_cast<std::istream::int_type>(EOF): return Ptr();
		case '\'': {
			ch = rest.get();
			Ptr quoted = parseElement(ch, rest);
			Ptr args = _state->creator()->new_pair(quoted, nullptr);
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

Ptr Parser::parse(std::istream &source) {
	std::istream::int_type ch = source.get();
    return parseElement(ch, source);
}

Ptr Parser::parse(const std::string &source) {
    std::istringstream in(source);
    Ptr result = parse(in);
	return result;
}

Ptr Parser::eval(std::istream &source) {
	return _state->eval(parse(source));
}

Ptr Parser::eval(const std::string &source) {
	std::istringstream in(source);
	return eval(in);
}

