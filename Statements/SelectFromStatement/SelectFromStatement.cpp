//
// Created by anzef on 20. 12. 2025.
//

#include "SelectFromStatement.h"

SelectFromStatement::SelectFromStatement(std::string table, std::vector<std::string> fields): table(std::move(table)), fields(std::move(fields)) {}

void SelectFromStatement::setTable(std::string table) {
    this->table = std::move(table);
}

void SelectFromStatement::setFields(std::vector<std::string> fields) {
   this->fields = std::move(fields);
}

void SelectFromStatement::addField(std::string newField) {
    this->fields.push_back(std::move(newField));
}

std::string SelectFromStatement::getTable() {
    return std::move(this->table);
};

std::vector<std::string> SelectFromStatement::getFields() {
    return std::move(this->fields);
};
