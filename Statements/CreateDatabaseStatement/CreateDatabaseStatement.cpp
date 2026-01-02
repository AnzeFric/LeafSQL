//
// Created by anzef on 30. 12. 2025.
//

#include "CreateDatabaseStatement.h"

CreateDatabaseStatement::CreateDatabaseStatement(std::string _name):
                                            name(std::move(_name)) {};

void CreateDatabaseStatement::setName(std::string _name) {
    this->name = std::move(_name);
};

std::string CreateDatabaseStatement::getName() {
    return this->name;
};
