//
// Created by anzef on 20. 12. 2025.
//

#include "SelectFromStatement.h"

SelectFromStatement::SelectFromStatement() {}

SelectFromStatement::SelectFromStatement(std::string table, const std::vector<std::string>& fields): table(std::move(table)), fields(fields) {}

void SelectFromStatement::setTable(const std::string& newTable) {
    this->table = newTable;
}

void SelectFromStatement::setFields(const std::string& newField) {
   this->fields.push_back(newField);
}
