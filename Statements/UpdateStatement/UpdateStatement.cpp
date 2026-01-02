//
// Created by anzef on 30. 12. 2025.
//

#include "UpdateStatement.h"

UpdateStatement::UpdateStatement(std::string table, std::vector<std::string> columns, std::vector<std::string> values): table(std::move(table)), columns(std::move(columns)), values(std::move(values)) {};

void UpdateStatement::setTable(std::string table) {
    this->table = std::move(table);
};

void UpdateStatement::setColumns(std::vector<std::string> columns) {
    this->columns = std::move(columns);
};

void UpdateStatement::setValues(std::vector<std::string> values) {
    this->values = std::move(values);
};

std::string UpdateStatement::getTable() {
    return std::move(this->table);
};

std::vector<std::string> UpdateStatement::getColumns() {
    return std::move(this->columns);
};

std::vector<std::string> UpdateStatement::getValues() {
    return std::move(this->values);
};
