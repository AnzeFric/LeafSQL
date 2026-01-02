//
// Created by anzef on 30. 12. 2025.
//

#include "DeleteFromStatement.h"

DeleteFromStatement::DeleteFromStatement(std::string _table):
                                    table(std::move(_table)) {};

void DeleteFromStatement::setTable(std::string _table) {
    this->table = std::move(_table);
};

std::string DeleteFromStatement::getTable() {
    return std::move(this->table);
};
