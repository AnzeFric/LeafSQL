//
// Created by anzef on 14. 12. 2025.
//

#ifndef LEAFSQL_QUERYPARSER_H
#define LEAFSQL_QUERYPARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "./Lexer/Lexer.h"
#include "../Statements/SelectFromStatement/SelectFromStatement.h"
#include "../Statements/InsertIntoStatement/InsertIntoStatement.h"
#include "../Token/Token.h"
#include "../Token/KeywordToken/KeywordToken.h"
#include "../Token/Types/KeywordType.h"
#include "../Statements/CreateStatement/CreateStatement.h"
#include "../QueryExecutor/QueryExecutor.h"

class QueryParser {
private:
    std::string query;
    std::vector<Token> tokens;
public:
    explicit QueryParser(std::string  query);
    void parseQuery();
    void print() const;
};

#endif //LEAFSQL_QUERYPARSER_H
