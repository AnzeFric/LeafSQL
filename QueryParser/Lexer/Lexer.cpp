//
// Created by anzef on 14. 12. 2025.
//

#include "Lexer.h"
#include <algorithm>
#include <optional>
#include "../../Token/Types/TokenType.h"
#include <iostream>

Lexer::Lexer(std::string _query): query(std::move(_query)), pos(0) {}

// Check if we call 'nextToken()' method after the End token was returned
void endTokenAlreadyIssuedError(const size_t& _pos, const std::string& _query) {
    if (_pos > _query.length() - 1) {
        throw std::runtime_error(std::string("Calling nextToken after end of query"));
    }
}

void skipWhitespace(size_t& _pos, const std::string& _query) {
    while (std::isspace(_query[_pos])) {
        _pos++;
    }
}

std::optional<Token> checkEndOfQuery(size_t& pos, const std::string& query) {
    if (pos == query.length() - 1) {
        ++pos;
        return Token{TokenType::End, ";"};
    }
    return std::nullopt;
}

std::optional<Token> checkExceptionChar(const char& c, size_t& _pos) {
    if (c == ',') {
        _pos++;
        return Token {TokenType::Comma, ","};
    }
    if (c == '*') {
        _pos++;
        return Token {TokenType::Everything, "*"};
    }
    if (c == '(' || c == ')') {
        _pos++;
        return Token {TokenType::Bracket, std::string(1, c)};
    }
    return std::nullopt;
}

// Move 'pos' to end of token
void incrementPosToEndOfToken(size_t& _pos, const std::string& _query, const std::vector<char>& _exceptionChar) {
    const size_t querySize = _query.size();

    // While the char is 'alnum' OR inside the exception arr, ex: 'created_at'
    while (_pos < querySize && (std::isalnum(_query[_pos]) || std::ranges::find(_exceptionChar, _query[_pos]) != _exceptionChar.end())) {
        _pos++;
    }

    // Check if the token is a function call, example: NOW()
    if (_pos + 1 < querySize && _query[_pos] == '(' && _query[_pos + 1] == ')') {
        _pos += 2;  // Include both '(' and ')'
    }
}

Token Lexer::nextToken() {
    endTokenAlreadyIssuedError(this->pos, this->query);

    skipWhitespace(this->pos, this->query);

    if (const std::optional<Token> _token = checkEndOfQuery(pos, query)) {
        return *_token;
    }

    // Comma, *, ( or )
    const char c = this->query[this->pos];
    if (const std::optional<Token> _token = checkExceptionChar(c, this->pos)) {
        return *_token;
    }

    // Other
    if (std::isalnum(c)) {
        const size_t start = this->pos;

        incrementPosToEndOfToken(this->pos, this->query, this->exceptionChar);

        const std::string word = this->query.substr(start, pos - start);

        // Convert to uppercase for keyword comparison
        std::string upper = word;
        std::ranges::transform(upper, upper.begin(), ::toupper);

        if (std::ranges::find(this->reservedWords, upper) != this->reservedWords.end()) {
            return Token {TokenType::Keyword, upper};
        }

        return Token {TokenType::Identifier, word};
    }

    // Error
    throw std::runtime_error(std::string("Unexpected character: ") + c);
}
