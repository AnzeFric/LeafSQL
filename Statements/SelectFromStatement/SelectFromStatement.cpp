//
// Created by anzef on 20. 12. 2025.
//

#include "SelectFromStatement.h"
#include <utility>

SelectFromStatement::SelectFromStatement(std::string _table, std::vector<std::string> _fields):
                                    table(std::move(_table)), fields(std::move(_fields)) {}

void SelectFromStatement::setTable(std::string _table) {
    this->table = std::move(_table);
}

void SelectFromStatement::setFields(std::vector<std::string> _fields) {
   this->fields = std::move(_fields);
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
