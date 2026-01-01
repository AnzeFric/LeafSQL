//
// Created by anzef on 1. 01. 2026.
//

#include "CreateTableStatement.h"

CreateTableStatement::CreateTableStatement() {};

CreateTableStatement::CreateTableStatement(std::string name): name(std::move(name)) {};

void CreateTableStatement::setName(const std::string& name) {
    this->name = name;
};
