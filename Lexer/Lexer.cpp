//
// Created by anzef on 14. 12. 2025.
//

#include "Lexer.h"

#include <iostream>

Lexer::Lexer(std::string query): query(std::move(query)), pos(0), token(Token(TokenType::Start, "")) {}

Token Lexer::nextToken() {
    if (pos > query.length() - 1) {
        // Error
        throw std::runtime_error(std::string("Calling nextToken after end of query"));
    }

    // Skip whitespace
    while (std::isspace(query[pos])) {
        pos++;
    }

    // End of query
    if (pos == query.length() - 1) {
        pos++;
        this->token = Token(TokenType::End, ";");
        return this->token;
    }

    // Comma or *
    const char c = query[pos];
    if (c == ',') {
        pos++;
        this->token = {TokenType::Comma, ","};
        return this->token;
    } else if (c == '*') {
        pos++;
        this->token = {TokenType::Everything, "*"};
        return this->token;
    }

    // Other
    if (std::isalpha(c)) {
        const size_t start = pos;

        while (pos < query.size() && std::isalnum(query[pos])) {
            pos++;
        }

        const std::string word = query.substr(start, pos - start);

        // Convert to uppercase for keyword comparison
        std::string upper = word;
        std::ranges::transform(upper, upper.begin(), ::toupper);

        // TODO: Add other keywords with an arr
        if (upper == "SELECT" || upper == "FROM") {
            this->token = {TokenType::Keyword, upper};
            return this->token;
        }

        this->token = {TokenType::Identifier, word};
        return this->token;
    }

    // Error
    throw std::runtime_error(std::string("Unexpected character: ") + c);
}

Token Lexer::getToken() {
    return this->token;
}
