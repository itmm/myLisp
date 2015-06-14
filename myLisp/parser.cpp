#include "parser.h"

#include <sstream>

#include "number.h"
#include "string.h"
#include "state.h"

Ptr Parser::parseNumber(std::istream::int_type &ch, std::istream &rest) {
    BigInt numerator = 0;
    BigInt denominator;
    bool negative = false;
    
    if (ch == '-') {
        negative = true;
        ch = rest.get();
    }
    
    while (isnumber(static_cast<int>(ch))) {
        numerator = numerator * 10 + (ch - '0');
        ch = rest.get();
    }
    if (ch == '/') {
        denominator = 0;
        ch = rest.get();
        while (isnumber(static_cast<int>(ch))) {
            denominator = denominator * 10 + (ch - '0');
            ch = rest.get();
        }
    } else {
        denominator = 1;
    }
    
    return _state->creator()->new_number(Fractional(numerator, denominator, negative));
}

Ptr Parser::parseString(std::istream::int_type &ch, std::istream &rest) {
    ch = rest.get();
    std::ostringstream buffer;
    while (ch != EOF && ch != '"') {
        buffer << (char) ch;
        ch = rest.get();
    }
    if (ch == '"') { ch = rest.get(); }
    return _state->creator()->new_string(buffer.str());
}

void Parser::eatSpace(std::istream::int_type &ch, std::istream &rest) {
    while (isspace(static_cast<int>(ch))) {
        ch = rest.get();
    }
}

Ptr Parser::parsePair(std::istream::int_type &ch, std::istream &rest) {
    if (ch == ')') {
        ch = rest.get();
        return Ptr(Pair::null(), _state->collector());
    }
    Ptr car = parseElement(ch, rest);
    if (!car) { return Ptr(nullptr, _state->collector()); }

    eatSpace(ch, rest);
    if (ch == '.') {
        ch = rest.get();
        Ptr cdr = parseElement(ch, rest);
        if (!cdr) { return Ptr(nullptr, _state->collector()); }
        return _state->creator()->new_pair(car, cdr);
    } else {
        Ptr cdr = parsePair(ch, rest);
        if (!cdr) { return Ptr(nullptr, _state->collector()); }
        return _state->creator()->new_pair(car, cdr);
    }
}

Ptr Parser::parseIdentifier(std::istream::int_type &ch, std::istream &rest) {
    std::ostringstream buffer;
    while (ch != EOF && !isspace(static_cast<int>(ch)) && ch != ')') {
        buffer << (char) ch;
        ch = rest.get();
    }
    return Ptr(_state->root()->as_dictionary()->get(buffer.str()), _state->collector());
}

Ptr Parser::parseElement(std::istream::int_type &ch, std::istream &rest) {
    eatSpace(ch, rest);
    switch (ch) {
        case static_cast<std::istream::int_type>(EOF): break;
        case '-':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            return parseNumber(ch, rest);
        case '"':
            return parseString(ch, rest);
        case '(':
            ch = rest.get();
            return parsePair(ch, rest);
        default:
            return parseIdentifier(ch, rest);
    }
    return Ptr(nullptr, _state->collector());
}

Ptr Parser::parse(std::istream &source) {
	std::istream::int_type ch = source.get();
    return parseElement(ch, source);
}

Ptr Parser::parse(const std::string &source) {
    std::istringstream in(source);
    return parse(in);
}

Ptr Parser::eval(std::istream &source) {
	return _state->eval(parse(source));
}

Ptr Parser::eval(const std::string &source) {
	std::istringstream in(source);
	return eval(in);
}

