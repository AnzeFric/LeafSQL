//
// Created by anzef on 30. 12. 2025.
//

#include "UpdateStatement.h"

UpdateStatement::UpdateStatement(std::string table, std::vector<std::string> columns, std::vector<std::string> values): table(std::move(table)), columns(std::move(columns)), values(std::move(values)) {};

void UpdateStatement::setTable(const std::string& table) {
    this->table = table;
};

void UpdateStatement::setColumns(const std::vector<std::string>& columns) {
    this->columns = columns;
};

void UpdateStatement::setValues(const std::vector<std::string>& values) {
    this->values = values;
};
