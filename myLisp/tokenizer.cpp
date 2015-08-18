#include "tokenizer.h"

void Tokenizer::read() {
    if (_ch != EOF) {
        _ch = _in.get();
        ++_pos;
    }
}

std::string Tokenizer::single_value() {
    std::string result;
    result.push_back(_ch);
    read();
    return result;
}

Token &Tokenizer::whitespace() {
    size_t begin = _pos;
    std::ostringstream buffer;
    while (_ch != EOF && isspace(_ch)) {
        buffer << static_cast<char>(_ch);
        read();
    }
    _token = Token(kTokenWhitespace, begin, buffer.str());
    return _token;
}

Token &Tokenizer::string() {
    size_t begin = _pos;
    std::ostringstream buffer;
    buffer << static_cast<char>(_ch);
    read();
    while (_ch != '"') {
        if (_ch == '\\') { buffer << static_cast<char>(_ch); read(); }
        if (_ch == EOF) { _token = Token(kTokenUnknown, begin, std::string()); return _token; }
        buffer << static_cast<char>(_ch);
        read();
    }
    buffer << static_cast<char>(_ch);
    read();
    _token = Token(kTokenString, begin, buffer.str());
    return _token;
}

Token &Tokenizer::comment(size_t begin, std::ostringstream &buffer) {
    while (_ch != EOF && _ch != '\n' && _ch != '\r') {
        buffer << static_cast<char>(_ch);
        read();
    }
    _token = Token(kTokenComment, begin, buffer.str());
    return _token;
}

bool Tokenizer::is_number(const std::string &str) {
    auto i = str.begin();
    auto e = str.end();
    if (i == e) return false;
    if (*i == '-') {
        ++i;
        if (i == e) return false;
    }
    for (; i != e; ++i) {
        if (!isdigit(*i)) break;
    }
    if (i == e) return true;
    if (*i != '/') return false;
    ++i;
    if (i == e) return false;
    for (; i != e; ++i) {
        if (!isdigit(*i)) break;
    }
    return i == e;
}

Token &Tokenizer::identifier() {
    size_t begin = _pos;
    std::ostringstream buffer;
    buffer << static_cast<char>(_ch);
    read();
    for (;;) {
        if (_ch == EOF || _ch == ')' || isspace(_ch)) break;
        buffer << static_cast<char>(_ch);
        read();
    }
    auto str = buffer.str();
    if (str.size() >= 2 && str[0] == ';' && str[1] == ';') {
        return comment(begin, buffer);
    }
    if (str == ".") {
        _token = Token(kTokenDot, begin, str);
        return _token;
    }
    _token = Token(is_number(str)? kTokenNumber : kTokenIdentifier, begin, str);
    return _token;
}

Token &Tokenizer::next() {
    if (_ch == EOF) { _token = Token(kTokenEof, _pos, std::string()); return _token; }
    if (isspace(static_cast<int>(_ch))) {
        return whitespace();
    }
    switch (_ch) {
        case '\'': _token = Token(kTokenQuote, _pos, single_value()); return _token;
        case '(': _token = Token(kTokenLeftParenthesis, _pos, single_value()); return _token;
        case ')': _token = Token(kTokenRightParenthesis, _pos, single_value()); return _token;
        case '"': return string();
    }
    return identifier();
}
