//
// Created by anzef on 20. 12. 2025.
//

#include "SelectFromStatement.h"

SelectFromStatement::SelectFromStatement(std::string table, const std::vector<std::string>& fields): table(std::move(table)), fields(fields) {}

void SelectFromStatement::setTable(std::string newTable) {
    this->table = std::move(newTable);
}

void SelectFromStatement::setFields(std::string newField) {
   this->fields.push_back(std::move(newField));
}

std::string SelectFromStatement::getTable() {
    return std::move(this->table);
};

std::vector<std::string> SelectFromStatement::getFields() {
    return std::move(this->fields);
};
