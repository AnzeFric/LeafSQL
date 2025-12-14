//
// Created by anzef on 14. 12. 2025.
//

#ifndef LEAFSQL_QUERYPARSER_H
#define LEAFSQL_QUERYPARSER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "../Lexer/Lexer.h"
#include "../Statements.h"

class QueryParser {
private:
    Lexer& lexer;
public:
    explicit QueryParser(Lexer& lexer);
    std::vector<std::string> parseQuery();
    std::string toString();
};

#endif //LEAFSQL_QUERYPARSER_H
