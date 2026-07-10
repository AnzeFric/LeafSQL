//
// Created by Uporabnik on 10. 07. 2026.
//

#include "UseDatabaseStatement.h"


UseDatabaseStatement::UseDatabaseStatement(std::string _name): name(std::move(_name)) {};

void UseDatabaseStatement::setName(std::string _name) {
    this->name = std::move(_name);
};

std::string UseDatabaseStatement::getName() const {
    return this->name;
};
