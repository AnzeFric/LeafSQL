//
// Created by anzef on 14. 12. 2025.
//

#include "./Lexer.h"

Lexer::Lexer(std::string query): query(std::move(query)), pos(0) {}

Token Lexer::nextToken() {
    // Skip whitespace
    while (pos < query.length() && std::isspace(query[pos])) {
        pos++;
    }

    // End of query
    if (pos >= query.length()) {
        return Token(Token::Type::End, "");
    }

    // Comma
    const char c = query[pos];
    if (c == ',') {
        pos++;
        return {Token::Type::Comma, ","};
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
            return {Token::Type::Keyword, upper};
        }

        return {Token::Type::Identifier, word};
    }

    // Error
    throw std::runtime_error(std::string("Unexpected character: ") + c);
}
