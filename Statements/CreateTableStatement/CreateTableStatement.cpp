//
// Created by anzef on 1. 01. 2026.
//

#include "CreateTableStatement.h"

CreateTableStatement::CreateTableStatement(std::string _name, std::vector<std::string> _columns, std::vector<std::vector<std::string>> _attributes):
                                        name(std::move(_name)), columns(std::move(_columns)), attributes(std::move(_attributes)) {};

void CreateTableStatement::setName(std::string _name) {
        this->name = std::move(_name);
};

void CreateTableStatement::setColumns(std::vector<std::string> _columns) {
        this->columns = std::move(_columns);
};

void CreateTableStatement::setAttributes(std::vector<std::vector<std::string>> _attributes) {
        this->attributes = std::move(_attributes);
};

std::string CreateTableStatement::getName() {
        return std::move(this->name);
}

std::vector<std::string> CreateTableStatement::getColumns() {
        return std::move(this->columns);
};

std::vector<std::vector<std::string>> CreateTableStatement::getAttributes() {
        return std::move(this->attributes);
};