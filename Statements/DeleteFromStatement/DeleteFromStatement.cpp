//
// Created by anzef on 30. 12. 2025.
//

#include "DeleteFromStatement.h"

DeleteFromStatement::DeleteFromStatement() {};

DeleteFromStatement::DeleteFromStatement(std::string table): table(std::move(table)) {};

void DeleteFromStatement::setTable(std::string table) {
    this->table = std::move(table);
};
