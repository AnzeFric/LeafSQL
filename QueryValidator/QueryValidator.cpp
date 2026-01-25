//
// Created by anzef on 25. 01. 2026.
//

#include "QueryValidator.h"

void QueryValidator::validateSelectQuery(SelectFromStatement selectFromStatement) {}

void QueryValidator::validateInsertQuery(InsertIntoStatement insertIntoStatement, const std::string& dbName) {}

void QueryValidator::validateUpdateQuery(UpdateStatement updateStatement) {}

void QueryValidator::validateDeleteQuery(DeleteFromStatement deleteFromStatement) {}

void QueryValidator::validateCreateDatabaseQuery(CreateDatabaseStatement createDatabaseStatement) {}

void QueryValidator::validateCreateTableQuery(CreateTableStatement createTableStatement, const std::string& dbName) {}
