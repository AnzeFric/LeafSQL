//
// Created by anzef on 30. 12. 2025.
//

#include "UpdateStatement.h"

UpdateStatement::UpdateStatement(std::string _table, std::vector<std::string> _columns, std::vector<std::string> _values):
                            table(std::move(_table)), columns(std::move(_columns)), values(std::move(_values)) {};

void UpdateStatement::setTable(std::string _table) {
    this->table = std::move(_table);
};

void UpdateStatement::setColumns(std::vector<std::string> _columns) {
    this->columns = std::move(_columns);
};

void UpdateStatement::setValues(std::vector<std::string> _values) {
    this->values = std::move(_values);
};

std::string UpdateStatement::getTable() const{
    return this->table;
};

std::vector<std::string> UpdateStatement::getColumns() const{
    return this->columns;
};

std::vector<std::string> UpdateStatement::getValues() const {
    return this->values;
};
