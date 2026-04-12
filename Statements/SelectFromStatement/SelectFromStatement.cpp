//
// Created by anzef on 20. 12. 2025.
//

#include "SelectFromStatement.h"
#include <utility>

SelectFromStatement::SelectFromStatement(std::string _table, std::vector<std::string> _columns):
                                    table(std::move(_table)), columns(std::move(_columns)) {}

void SelectFromStatement::setTable(std::string _table) {
    this->table = std::move(_table);
}

void SelectFromStatement::setColumns(std::vector<std::string> _columns) {
   this->columns = std::move(_columns);
}

void SelectFromStatement::addColumn(std::string _column) {
    this->columns.push_back(std::move(_column));
}

std::string SelectFromStatement::getTable() {
    return std::move(this->table);
};

std::vector<std::string> SelectFromStatement::getColumns() {
    return std::move(this->columns);
};
