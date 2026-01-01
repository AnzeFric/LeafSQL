//
// Created by anzef on 21. 12. 2025.
//

#include "QueryExecutor.h"

QueryExecutor::QueryExecutor() {}

void QueryExecutor::executeSelectQuery(const SelectFromStatement& selectFromStatement) const {};

void QueryExecutor::executeInsertQuery(const InsertIntoStatement& insertIntoStatement) const {};

void QueryExecutor::executeUpdateQuery(const UpdateStatement& updateStatement) const {};

void QueryExecutor::executeDeleteQuery(const DeleteFromStatement& deleteFromStatement) const {};

void QueryExecutor::executeCreateDatabaseQuery(const CreateDatabaseStatement& createDatabaseStatement) const {};

void QueryExecutor::executeCreateTableQuery(const CreateTableStatement& createTableStatement) const {};
