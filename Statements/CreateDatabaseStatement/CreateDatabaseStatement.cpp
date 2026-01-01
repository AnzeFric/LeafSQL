//
// Created by anzef on 30. 12. 2025.
//

#include "CreateStatement.h"

CreateStatement::CreateStatement() {};

CreateStatement::CreateStatement(std::string name, bool isTable): name(std::move(name)), isTable(std::move(isTable)) {};

void CreateStatement::setName(const std::string& name) {
    this->name = name;
};

void CreateStatement::setIsTable(const bool& isTable) {
    this->isTable = isTable;
};
