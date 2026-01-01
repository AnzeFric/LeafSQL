//
// Created by anzef on 30. 12. 2025.
//

#include "CreateDatabaseStatement.h"

CreateDatabaseStatement::CreateDatabaseStatement() {};

CreateDatabaseStatement::CreateDatabaseStatement(std::string name): name(std::move(name)) {};

void CreateDatabaseStatement::setName(const std::string& name) {
    this->name = name;
};
