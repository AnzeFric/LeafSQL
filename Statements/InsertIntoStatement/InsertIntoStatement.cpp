//
// Created by anzef on 30. 12. 2025.
//

#include "InsertIntoStatement.h"

InsertIntoStatement::InsertIntoStatement(std::string table, std::vector<std::string> columns, std::vector<std::string> values): table(std::move(table)), columns(std::move(columns)), values(std::move(values)) {};

void InsertIntoStatement::setTable(std::string table) {
    this->table = std::move(table);
};

void InsertIntoStatement::setColumns(std::vector<std::string> columns) {
    this->columns = std::move(columns);
};

void InsertIntoStatement::setValues(std::vector<std::string> values) {
    this->values = std::move(values);
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
