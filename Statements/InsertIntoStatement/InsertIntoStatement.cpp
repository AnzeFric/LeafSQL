//
// Created by anzef on 30. 12. 2025.
//

#include "InsertIntoStatement.h"

InsertIntoStatement::InsertIntoStatement(std::string _table, std::vector<std::string> _columns, std::vector<std::string> _values):
                                    table(std::move(_table)), columns(std::move(_columns)), values(std::move(_values)) {};

void InsertIntoStatement::setTable(std::string _table) {
    this->table = std::move(_table);
};

void InsertIntoStatement::setColumns(std::vector<std::string> _columns) {
    this->columns = std::move(_columns);
};

void InsertIntoStatement::setValues(std::vector<std::string> _values) {
    this->values = std::move(_values);
};

std::string InsertIntoStatement::getTable() {
    return std::move(this->table);
};

std::vector<std::string> InsertIntoStatement::getColumns() {
    return std::move(this->columns);
};

std::vector<std::string> InsertIntoStatement::getValues() {
    return std::move(this->values);
};
