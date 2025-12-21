//
// Created by anzef on 21. 12. 2025.
//

#ifndef LEAFSQL_QUERYEXECUTOR_H
#define LEAFSQL_QUERYEXECUTOR_H

#include <utility>
#include "../SelectFromStatement/SelectFromStatement.h"

class QueryExecutor {
private:
    SelectFromStatement selectFromStatement;
public:
    QueryExecutor(SelectFromStatement selectFromStatement);
    void executeSelectQuery() const;
    void executeInsertQuery() const;
    void executeDeleteQuery() const;
    void executeUpdateQuery() const;
};

#endif //LEAFSQL_QUERYEXECUTOR_H
