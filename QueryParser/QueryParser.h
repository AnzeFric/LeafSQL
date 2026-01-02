//
// Created by anzef on 14. 12. 2025.
//

#ifndef LEAFSQL_QUERYPARSER_H
#define LEAFSQL_QUERYPARSER_H

#include <string>
#include <vector>
#include "../Token/Token.h"

class QueryParser {
private:
    std::string query;
    std::vector<Token> tokens;
public:
    explicit QueryParser(std::string _query);
    void parseQuery();
    void print() const;
};

#endif //LEAFSQL_QUERYPARSER_H
