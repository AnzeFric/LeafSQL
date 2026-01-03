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
    QueryExecutor() = default;
    static void executeSelectQuery(const SelectFromStatement& selectFromStatement);
    static void executeInsertQuery(const InsertIntoStatement& insertIntoStatement);
    static void executeUpdateQuery(const UpdateStatement& updateStatement);
    static void executeDeleteQuery(const DeleteFromStatement& deleteFromStatement);
    static void executeCreateDatabaseQuery(CreateDatabaseStatement createDatabaseStatement);
    static void executeCreateTableQuery(CreateTableStatement createTableStatement, const std::string& dbName);
};

#endif //LEAFSQL_QUERYEXECUTOR_H
