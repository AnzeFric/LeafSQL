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
    std::string dbName;

    void parseUseDatabaseQuery(Lexer& lexer);
public:
    explicit QueryParser(std::string _query);
    [[nodiscard]] std::string getDbName() const;
    void setDbName(std::string _dbName);
    void setQuery(std::string _query);
    void parseQuery();
};

#endif //LEAFSQL_QUERYPARSER_H
