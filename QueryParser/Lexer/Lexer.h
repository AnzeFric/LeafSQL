//
// Created by anzef on 14. 12. 2025.
//

#ifndef LEAFSQL_LEXER_H
#define LEAFSQL_LEXER_H

#include "../../Token/Token.h"
#include <stdexcept>

class Lexer {
private:
    std::string query;
    size_t pos;
    Token token;
public:
    explicit Lexer(std::string _query);
    Token nextToken();
    Token getToken();
};

#endif //LEAFSQL_LEXER_H
