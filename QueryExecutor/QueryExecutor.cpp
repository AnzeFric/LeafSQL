//
// Created by anzef on 21. 12. 2025.
//

#include "QueryExecutor.h"

QueryExecutor::QueryExecutor(SelectFromStatement selectFromStatement): selectFromStatement(std::move(selectFromStatement)) {}

void QueryExecutor::executeSelectQuery() const {}
void QueryExecutor::executeInsertQuery() const {}
void QueryExecutor:: executeDeleteQuery() const {}
void QueryExecutor::executeUpdateQuery() const {}
