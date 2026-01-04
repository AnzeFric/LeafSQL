//
// Created by anzef on 14. 12. 2025.
//

#ifndef LEAFSQL_LEXER_H
#define LEAFSQL_LEXER_H

#include "../../Token/Token.h"
#include <stdexcept>
#include <vector>

class Lexer {
private:
    std::string query;
    size_t pos;
    const std::vector<std::string> reservedWords = {"SELECT", "FROM", "INSERT", "INTO", "CREATE", "TABLE", "USE", "DATABASE", "UPDATE"};
    const std::vector<char> exceptionChar = {'.', '@', '_', '-'};
public:
    explicit Lexer(std::string _query);
    Token nextToken();
};

#endif //LEAFSQL_LEXER_H
