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
#include  "../Statements/UseDatabaseStatement/UseDatabaseStatement.h"

class QueryValidator {
public:
    QueryValidator() = default;
    static void validateSelectQuery(const std::vector<int>& columnIndexes, const std::string& tableName);
    static void validateInsertQuery( std::fstream& dataFile,
                                    const std::vector<std::string>& tableColumns,
                                    const std::vector<std::string>& tableAttributes,
                                    const std::vector<std::string>& insertColumns,
                                    const std::vector<std::string>& insertValues);
    static void validateUpdateQuery(UpdateStatement updateStatement);
    static void validateDeleteQuery(DeleteFromStatement deleteFromStatement);
    static void validateCreateDatabaseQuery(const CreateDatabaseStatement& createDatabaseStatement);
    static void validateCreateTableQuery(const CreateTableStatement& createTableStatement);
    static void validateUseDatabaseQuery(const UseDatabaseStatement& useDatabaseStatement);
};

#endif //LEAFSQL_QUERYVALIDATOR_H
