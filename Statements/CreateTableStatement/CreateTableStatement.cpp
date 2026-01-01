//
// Created by anzef on 1. 01. 2026.
//

#include "CreateTableStatement.h"

CreateTableStatement::CreateTableStatement(std::string name, std::vector<std::string> columns, std::vector<std::vector<std::string>> attributes) :
        name(std::move(name)), columns(std::move(columns)), attributes(std::move(attributes)) {};

void CreateTableStatement::setName(const std::string& name) {
        this->name = name;
};

void CreateTableStatement::setColumns(const std::vector<std::string>& columns) {
        this->columns = columns;
};

void CreateTableStatement::setAttributes(const std::vector<std::vector<std::string>>& attributes) {
        this->attributes = attributes;
};
