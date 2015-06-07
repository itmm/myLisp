#include "parser.h"

#include <sstream>

#include "number.h"
#include "string.h"

Number *Parser::parseNumber(std::istream::int_type &ch, std::istream &rest) {
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
    
    return new Number(Fractional(numerator, denominator, negative));
}

String *Parser::parseString(std::istream::int_type &ch, std::istream &rest) {
    ch = rest.get();
    std::ostringstream buffer;
    while (ch != EOF && ch != '"') {
        buffer << (char) ch;
        ch = rest.get();
    }
    if (ch == '"') { ch = rest.get(); }
    return new String(buffer.str());
}

void Parser::eatSpace(std::istream::int_type &ch, std::istream &rest) {
    while (isspace(static_cast<int>(ch))) {
        ch = rest.get();
    }
}

Pair *Parser::parsePair(std::istream::int_type &ch, std::istream &rest) {
    if (ch == ')') {
        ch = rest.get();
        return Pair::null();
    }
    Element *car = parseElement(ch, rest);
    if (!car) { return nullptr; }

    eatSpace(ch, rest);
    if (ch == '.') {
        ch = rest.get();
        Element *cdr = parseElement(ch, rest);
        if (!cdr) { _collector->release_initial_lock(car); car->free(); return nullptr; }
        Pair *result = _collector->new_pair(car, cdr);
		_collector->release_initial_lock(car);
		_collector->release_initial_lock(cdr);
        return result;
    } else {
        Pair *cdr = parsePair(ch, rest);
        if (!cdr) { _collector->release_initial_lock(car); car->free(); return nullptr; }
        Pair *result = _collector->new_pair(car, cdr);
		_collector->release_initial_lock(car);
		_collector->release_initial_lock(cdr);
        return result;
    }
}

Element *Parser::parseIdentifier(std::istream::int_type &ch, std::istream &rest) {
    std::ostringstream buffer;
    while (ch != EOF && !isspace(static_cast<int>(ch))) {
        buffer << (char) ch;
        ch = rest.get();
    }
    return _context->get(buffer.str());
}

Element *Parser::parseElement(std::istream::int_type &ch, std::istream &rest) {
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
    return nullptr;
}

Element *Parser::parse(std::istream &source) {
	std::istream::int_type ch = source.get();
    Element *result = parseElement(ch, source);
    return result;
}

Element *Parser::parse(const std::string &source) {
    std::istringstream in(source);
    return parse(in);
}
