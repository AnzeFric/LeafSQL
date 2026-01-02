//
// Created by anzef on 21. 12. 2025.
//

#ifndef LEAFSQL_QUERYEXECUTOR_H
#define LEAFSQL_QUERYEXECUTOR_H

#include <utility>
#include "../Statements/SelectFromStatement/SelectFromStatement.h"
#include "../Statements/InsertIntoStatement/InsertIntoStatement.h"
#include "../Statements/UpdateStatement/UpdateStatement.h"
#include "../Statements/DeleteFromStatement/DeleteFromStatement.h"
#include "../Statements/CreateDatabaseStatement/CreateDatabaseStatement.h"
#include "../Statements/CreateTableStatement/CreateTableStatement.h"

class QueryExecutor {
public:
    QueryExecutor();
    void executeSelectQuery(const SelectFromStatement& selectFromStatement) const;
    void executeInsertQuery(const InsertIntoStatement& insertIntoStatement) const;
    void executeUpdateQuery(const UpdateStatement& updateStatement) const;
    void executeDeleteQuery(const DeleteFromStatement& deleteFromStatement) const;
    void executeCreateDatabaseQuery(CreateDatabaseStatement createDatabaseStatement);
    void executeCreateTableQuery(const CreateTableStatement& createTableStatement) const;
};

#endif //LEAFSQL_QUERYEXECUTOR_H
