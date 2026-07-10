//
// Created by anzef on 14. 12. 2025.
//

#ifndef LEAFSQL_QUERYPARSER_H
#define LEAFSQL_QUERYPARSER_H

#include <string>
#include "./Lexer/Lexer.h"

class QueryParser {
private:
    std::string query;

    static void parseUseDatabaseQuery(Lexer& lexer);
public:
    explicit QueryParser(std::string _query);
    void setQuery(std::string _query);
    void parseQuery() const;
};

#endif //LEAFSQL_QUERYPARSER_H
