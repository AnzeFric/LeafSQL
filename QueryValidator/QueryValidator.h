//
// Created by anzef on 25. 01. 2026.
//

#ifndef LEAFSQL_QUERYVALIDATOR_H
#define LEAFSQL_QUERYVALIDATOR_H

#include "../Statements/SelectFromStatement/SelectFromStatement.h"
#include "../Statements/UpdateStatement/UpdateStatement.h"
#include "../Statements/DeleteFromStatement/DeleteFromStatement.h"
#include "../Statements/CreateDatabaseStatement/CreateDatabaseStatement.h"
#include "../Statements/CreateTableStatement/CreateTableStatement.h"

class QueryValidator {
public:
    QueryValidator() = default;
    static void validateSelectQuery(SelectFromStatement selectFromStatement);
    static void validateInsertQuery( std::fstream& dataFile,
                                    const std::vector<std::string>& tableColumns,
                                    const std::vector<std::string>& tableAttributes,
                                    const std::vector<std::string>& insertColumns,
                                    const std::vector<std::string>& insertValues);
    static void validateUpdateQuery(UpdateStatement updateStatement);
    static void validateDeleteQuery(DeleteFromStatement deleteFromStatement);
    static void validateCreateDatabaseQuery(CreateDatabaseStatement createDatabaseStatement);
    static void validateCreateTableQuery(CreateTableStatement createTableStatement, const std::string& dbName);
};

#endif //LEAFSQL_QUERYVALIDATOR_H
