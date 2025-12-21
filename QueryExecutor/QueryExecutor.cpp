//
// Created by anzef on 21. 12. 2025.
//

#include "QueryExecutor.h"

#include <utility>

QueryExecutor::QueryExecutor(SelectFromStatement selectFromStatement): selectFromStatement(std::move(selectFromStatement)) {}

void QueryExecutor::executeQuery() const {

}
