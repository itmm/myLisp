#include "parser.h"

#include <cctype>
#include <sstream>

#include "number.h"
#include "pair.h"
#include "string.h"

Number *Parser::parseNumber(int &ch, std::istream &rest) {
    BigInt numerator = 0;
    BigInt denomerator;
    bool negative = false;
    
    if (ch == '-') {
        negative = true;
        ch = rest.get();
    }
    
    while (isnumber(ch)) {
        numerator = numerator * 10 + (ch - '0');
        ch = rest.get();
    }
    if (ch == '/') {
        denomerator = 0;
        ch = rest.get();
        while (isnumber(ch)) {
            denomerator = denomerator * 10 + (ch - '0');
            ch = rest.get();
        }
    } else {
        denomerator = 1;
    }
    
    return new Number(Fractional(numerator, denomerator, negative));
}

String *Parser::parseString(int &ch, std::istream &rest) {
    ch = rest.get();
    std::ostringstream buffer;
    while (ch != EOF && ch != '"') {
        buffer << (char) ch;
        ch = rest.get();
    }
    if (ch == '"') { ch = rest.get(); }
    return new String(buffer.str());
}

void Parser::eatSpace(int &ch, std::istream &rest) {
    while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
        ch = rest.get();
    }
}

Pair *Parser::parsePair(int &ch, std::istream &rest) {
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
        if (!cdr) { car->free(); return nullptr; }
        return _collector->new_pair(car, cdr);
    } else {
        Pair *cdr = parsePair(ch, rest);
        if (!cdr) { car->free(); return nullptr; }
        return _collector->new_pair(car, cdr);
    }
}

Element *Parser::parseElement(int &ch, std::istream &rest) {
    eatSpace(ch, rest);
    switch (ch) {
        case EOF: break;
        case '-':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            return parseNumber(ch, rest);
        case '"':
            return parseString(ch, rest);
        case '(':
            ch = rest.get();
            return parsePair(ch, rest);
    }
    return nullptr;
}

Element *Parser::parse(std::istream &source) {
    int ch = source.get();
    Element *result = parseElement(ch, source);
    return result;
}

Element *Parser::parse(const std::string &source) {
    std::istringstream in(source);
    return parse(in);
}
