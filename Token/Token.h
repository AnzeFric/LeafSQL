//
// Created by anzef on 21. 12. 2025.
//

#ifndef LEAFSQL_TOKEN_H
#define LEAFSQL_TOKEN_H

#include <string>
#include <utility>
#include "Types/TokenType.h"

class Token {
protected:
    TokenType type;
    std::string value;

public:
    Token(const TokenType type, std::string value): type(type), value(std::move(value)) {};
    Token(const Token& token): type(token.getType()), value(token.getValue()) {};
    
    TokenType getType() const { return this->type; };
    std::string getValue() const { return this->value; };
};

#endif //LEAFSQL_TOKEN_H
