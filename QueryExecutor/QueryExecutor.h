//
// Created by anzef on 21. 12. 2025.
//

#ifndef LEAFSQL_QUERYEXECUTOR_H
#define LEAFSQL_QUERYEXECUTOR_H

#include "../Statements/SelectFromStatement/SelectFromStatement.h"
#include "../Statements/InsertIntoStatement/InsertIntoStatement.h"
#include "../Statements/UpdateStatement/UpdateStatement.h"
#include "../Statements/DeleteFromStatement/DeleteFromStatement.h"
#include "../Statements/CreateDatabaseStatement/CreateDatabaseStatement.h"
#include "../Statements/CreateTableStatement/CreateTableStatement.h"

class QueryExecutor {
public:
    QueryExecutor() = default;
    static void executeSelectQuery(SelectFromStatement selectFromStatement);
    static void executeInsertQuery( std::fstream& dataFile,
                                    const std::vector<std::string>& tableColumns,
                                    const std::vector<std::string>& tableAttributes,
                                    const std::vector<std::string>& insertColumns,
                                    const std::vector<std::string>& insertValues);
    static void executeUpdateQuery(UpdateStatement updateStatement);
    static void executeDeleteQuery(DeleteFromStatement deleteFromStatement);
    static void executeCreateDatabaseQuery(CreateDatabaseStatement createDatabaseStatement);
    static void executeCreateTableQuery(CreateTableStatement createTableStatement, const std::string& dbName);
};

#endif //LEAFSQL_QUERYEXECUTOR_H
