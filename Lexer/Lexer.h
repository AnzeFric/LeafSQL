//
// Created by anzef on 14. 12. 2025.
//

#ifndef LEAFSQL_LEXER_H
#define LEAFSQL_LEXER_H

#include "../Token.h"
#include <stdexcept>
#include <algorithm>

class Lexer {
private:
    std::string query;
    size_t pos;
    Token token;
public:
    explicit Lexer(std::string query);
    Token nextToken();
    Token getToken();
};

#endif //LEAFSQL_LEXER_H
