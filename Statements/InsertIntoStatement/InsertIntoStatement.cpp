//
// Created by anzef on 30. 12. 2025.
//

#include "InsertIntoStatement.h"

InsertIntoStatement::InsertIntoStatement() {};

InsertIntoStatement::InsertIntoStatement(std::string table, std::vector<std::string> columns, std::vector<std::string> values): table(std::move(table)), columns(std::move(columns)), values(std::move(values)) {};

void InsertIntoStatement::setTable(const std::string& table) {
    this->table = table;
};

void InsertIntoStatement::setColumns(const std::vector<std::string>& columns) {
    this->columns = columns;
};

void InsertIntoStatement::setValues(const std::vector<std::string>& values) {
    this->values = values;
};
