//
// Created by anzef on 25. 01. 2026.
//

#ifndef LEAFSQL_QUERYPREPARER_H
#define LEAFSQL_QUERYPREPARER_H

#include "../Statements/SelectFromStatement/SelectFromStatement.h"
#include "../Statements/InsertIntoStatement/InsertIntoStatement.h"
#include "../Statements/UpdateStatement/UpdateStatement.h"
#include "../Statements/DeleteFromStatement/DeleteFromStatement.h"
#include "../Statements/CreateDatabaseStatement/CreateDatabaseStatement.h"
#include "../Statements/CreateTableStatement/CreateTableStatement.h"

class QueryPreparer {
public:
    QueryPreparer() = default;
    static void prepareSelectQuery(SelectFromStatement selectFromStatement);
    static void prepareInsertQuery(InsertIntoStatement insertIntoStatement, const std::string& dbName);
    static void prepareUpdateQuery(UpdateStatement updateStatement);
    static void prepareDeleteQuery(DeleteFromStatement deleteFromStatement);
    static void prepareCreateDatabaseQuery(CreateDatabaseStatement createDatabaseStatement);
    static void prepareCreateTableQuery(CreateTableStatement createTableStatement, const std::string& dbName);
};


#endif //LEAFSQL_QUERYPREPARER_H